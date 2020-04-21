package spiders

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"sync"

	"github.com/gocolly/colly"
	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/transform"
)

var (
	PeopleNewsCategory = make(map[string]string)
)

func pushIntoPeopleMap(key, val string) {
	if key == "http://www.people.com.cn/" {
		return
	}
	if val == "知识产权" {
		val = "知产"
	}
	PeopleNewsCategory[key] = val
}

func SpiderPeople() (titles, links, categories []string, source string) {
	domain := PeopleNewsDomain
	var mutex sync.RWMutex
	c := colly.NewCollector(
		colly.MaxDepth(SpiderDepth),
		colly.UserAgent("Opera/9.80 (Windows NT 6.1; U; zh-cn) Presto/2.9.168 Version/11.50"),
	)

	//var category string
	c.OnRequest(func(r *colly.Request) {
		r.Headers.Set("Host", "people.com.cn")
		r.Headers.Set("Connection", "keep-alive")
		r.Headers.Set("Accept", "/")
		r.Headers.Set("Origin", "")
		r.Headers.Set("Referer", "http://news.people.com.cn")
		r.Headers.Set("Accept-Encoding", "gzip, deflate")
		r.Headers.Set("Accept-Language", "gbk")
	})

	c.OnHTML("title", func(e *colly.HTMLElement) {
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach("#rwb_nav a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			category := el.Text
			pushIntoPeopleMap(link, category)
			e.Request.Visit(link)
		})
	})

	// 这里link捕获的是相对路径如：/n1/2020/0411/c1008-31670007.html
	// 要加上他分类标签的地址sig如：http://society.people.com.cn/
	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach(".jsnew_line a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			title := el.Text
			sig := fmt.Sprintf("%v", e.Request.URL)
			category := PeopleNewsCategory[sig]
			link = sig + link[1:]
			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach("#focus_list a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			title := el.Text
			sig := fmt.Sprintf("%v", e.Request.URL)
			category := PeopleNewsCategory[sig]
			//fmt.Printf("%s %s %s\n", category, title, link)
			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnResponse(func(r *colly.Response) {
		// 编码转换
		reader := transform.NewReader(bytes.NewReader(r.Body), simplifiedchinese.GBK.NewDecoder())
		//reader := transform.NewReader(bytes.NewReader(r.Body), simplifiedchinese.GBK.NewEncoder())
		b, _ := ioutil.ReadAll(reader)
		r.Body = b

		fileName := buildStorePageName(r.Request.URL.Hostname())
		r.Save(fileName)
	})

	c.Limit(&colly.LimitRule{
		Parallelism: SpiderParal,
		Delay:       SpiderTimeout,
	})

	c.Visit(domain)
	return titles, links, categories, SourcePeopleNews
}
