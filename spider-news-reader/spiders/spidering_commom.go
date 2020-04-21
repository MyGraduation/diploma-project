package spiders

import (
	"fmt"
	"os"
	"strings"
	"sync"
	"time"
)

const (
	BaiDuNewsDomain = "http://news.baidu.com"
	//PeopleNewsDomain = "http://news.people.com.cn"
	PeopleNewsDomain = "http://politics.people.com.cn"
	ChinaNewsDomain  = "http://www.chinanews.com"

	SourceBaiduNews  = "百度新闻"
	SourcePeopleNews = "人民网"
	SourceChinaNews  = "中国新闻网"
)

/*
func index() int {
	mutex.Lock()
	defer mutex.Unlock()
	i++
	return i
}
*/

func DebugOutput(category, title, link, requestURI string, m map[string]string) {
	fmt.Println("=================================================")
	fmt.Printf("分类: %s\n", category)
	fmt.Printf("标题: %s\n", title)
	fmt.Printf("链接: %s\n", link)
	fmt.Printf("请求链接: %s\n", requestURI)
	fmt.Printf("映射表: %+v\n", m)
	fmt.Println("=================================================\n")
}

const (
	SpiderTimeout = 3 * time.Minute
	SpiderParal   = 10
	SpiderDepth   = 3
	MaxStrSize    = 80
)

func appendNews(mutex *sync.RWMutex, titles, links, categories *[]string, title, link, category string) {
	if title == "" || link == "" || category == "" || len(title) > MaxStrSize || len(link) > MaxStrSize {
		return
	}
	if !strings.Contains(link, "http") || len(title) < 10 {
		return
	}
	link = strings.Trim(link, "\n")
	title = strings.Trim(title, "\n")
	category = strings.Trim(category, "\n")
	/*
		if link[len(link)-1] == '\n' {
			link = link[:len(link)-1]
		}
		if link[0] == '\n' {
			link = link[1:]
		}
		if title[len(title)-1] == '\n' {
			title = title[:len(title)-1]
		}
		if title[0] == '\n' {
			title = title[1:]
		}
	*/
	mutex.Lock()
	defer mutex.Unlock()
	*titles = append(*titles, title)
	*links = append(*links, link)
	*categories = append(*categories, category)
}

func AppendToNewsFile(title, link string) error {
	today := time.Unix(time.Now().Unix(), 0).Format("2006-01-02")
	fileName := "./news/news_" + today
	f, err := os.OpenFile(fileName, os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0666)
	if err != nil {
		return err
	}
	defer f.Close()
	content := fmt.Sprintf("%-30q\t%v", title, link)
	f.Write([]byte(content))
	f.Write([]byte("\n"))
	return nil
}

func buildStorePageName(host string) string {
	basePath := "./news/pages/"
	today := time.Unix(time.Now().Unix(), 0).Format("2006-01-02")
	return fmt.Sprintf("%s/%s_%s.html", basePath, host, today)
}
