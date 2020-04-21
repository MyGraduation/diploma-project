package main

import (
	"fmt"
	"net/http"
	"time"
	"bytes"
	"io/ioutil"
	"os"
	"errors"

	"github.com/spider-news-reader/spiders"
	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/transform"
)

const (
	StoreURL = "http://localhost:8080/v1/insert_news_meta?title=%s&&link=%s&&category=%s&&source=%s"
	Slowly   = 30 * time.Millisecond
	Period	 = 12 * time.Hour
)

type spiderFunc func() ([]string, []string, []string, string)

func Store(title, link, category, source string) error {
	_, err := http.Get(fmt.Sprintf(StoreURL, title, link, category, source))
	if err != nil {
		return err
	}
	return nil
}

func appendToFile(fileName, content string) error {
	if fileName == "" {
		return errors.New("null file path")
	}
	f, err := os.OpenFile(fileName, os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0666)
	if err != nil {
		return err
	}
	defer f.Close()
	f.Write([]byte(content))
	f.Write([]byte("\n"))
	return nil
}

// test store in file
func StoreLocalNewsInfo(title, link, source string) {
	today := time.Unix(time.Now().Unix(), 0).Format("200612")
	storeFile := "/root/news-info/Txt" + today
	content := fmt.Sprintf("<1>%v<1><2>%v--%v<2><t>%v<t>", link, title, source, today)
	reader := transform.NewReader(bytes.NewReader([]byte(content)), simplifiedchinese.GBK.NewDecoder())
	d, _ := ioutil.ReadAll(reader)
	content = string(d)
	appendToFile(storeFile, content)
}

func DealNewsWithSpider(f spiderFunc) {
	titles, links, categories, source := f()
	for i := 0; i < len(titles); i++ {
		spiders.AppendToNewsFile(titles[i], links[i])
		fmt.Printf("%v %v %v %v\n", source, categories[i], titles[i], links[i])
		Store(titles[i], links[i], categories[i], source)
		//StoreLocalNewsInfo(titles[i], links[i], source)
		time.Sleep(Slowly)
	}
}

func PrintNewsWithSpider(f spiderFunc) {
	titles, links, categories, source := f()
	for i := 0; i < len(titles); i++ {
		fmt.Printf("%d %v %v %v %v\n", i, source, categories[i], titles[i], links[i])
	}
}

func main() {
	for {
		DealNewsWithSpider(spiders.SpiderBaiduNews)
		DealNewsWithSpider(spiders.SpiderPeople)
		DealNewsWithSpider(spiders.SpiderChina)

		time.Sleep(Period)
	}

	//StoreLocalNewsInfo()

	//PrintNewsWithSpider(spiders.SpiderBaiduNews)
	//PrintNewsWithSpider(spiders.SpiderPeople)
	//PrintNewsWithSpider(spiders.SpiderChina)

	//spiders.SpiderBaiduNews()
	//spiders.SpiderPeople()
	//spiders.SpiderChina()
}
