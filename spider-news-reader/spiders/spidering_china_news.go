package spiders

import (
	//"fmt"

	"strings"
	"sync"

	"github.com/gocolly/colly"
)

var (
	/*
		ChinaNewsCategory = map[string]string{
			"www.chinanews.com/china/":         "国内",
			"www.chinanews.com/finance":        "财经",
			"www.chinanews.com/fortune/":       "金融",
			"www.chinanews.com/house/gd.shtml": "房产",
			"www.chinanews.com/mil/news.shtml": "军事",
			"www.chinanews.com/society/":       "社会",
			"www.chinanews.com/stock/gd.shtml": "证券",
			"www.chinanews.com/world/":         "国际",
		}
	*/

	// 头疼应对英语拼音混用的网页制作者
	ChinaNewsCategory = map[string]string{
		"/gn/":    "国内",
		"/cj/":    "财经",
		"/jr/":    "金融",
		"/house/": "房产",
		"/mil/":   "军事",
		"/sh/":    "社会",
		"/zj/":    "证券",
		"/gj/":    "国际",
		"/ty/":    "体育",
		"/hr/":    "华人",
	}
)

func pushIntoChinaMap(key, val string) {
	if val == "首页" {
		return
	}
	if val == "滚动" {
		val = "焦点"
	}
	ChinaNewsCategory[key] = val
}

func getFromChinaMap(key string) string {
	for k, v := range ChinaNewsCategory {
		if strings.Contains(key, k) {
			return v
		}
	}
	return ""
}

func SpiderChina() (titles, links, categories []string, source string) {
	var mutex sync.RWMutex
	c := colly.NewCollector(
		colly.MaxDepth(SpiderDepth),
		colly.UserAgent("Opera/9.80 (Windows NT 6.1; U; zh-cn) Presto/2.9.168 Version/11.50"),
	)

	c.OnRequest(func(r *colly.Request) {
		r.Headers.Set("Host", "people.com.cn")
		r.Headers.Set("Connection", "keep-alive")
		r.Headers.Set("Accept", "/")
		r.Headers.Set("Origin", "")
		r.Headers.Set("Referer", ChinaNewsDomain)
		r.Headers.Set("Accept-Encoding", "gzip, deflate")
		r.Headers.Set("Accept-Language", "gbk")
	})

	c.OnHTML("title", func(e *colly.HTMLElement) {
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach(".group a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			category := el.Text
			pushIntoChinaMap(link, category)
			e.Request.Visit(link)
		})
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach(".dd_bt a", func(i int, el *colly.HTMLElement) {
			link := "http:" + el.Attr("href")
			title := el.Text

			//sig := fmt.Sprintf("%v", e.Request.URL)
			category := getFromChinaMap(link)

			//DebugOutput(category, title, link, sig, ChinaNewsCategory)

			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach(".moren_right_nopic a", func(i int, el *colly.HTMLElement) {
			link := "http:" + el.Attr("href")
			title := el.Text

			//sig := fmt.Sprintf("%v", e.Request.URL)
			category := getFromChinaMap(link)
			//DebugOutput(category, title, link, sig, ChinaNewsCategory)

			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})
	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach(".tpo a", func(i int, el *colly.HTMLElement) {
			link := "http:" + el.Attr("href")
			title := el.Text
			if strings.Contains(link, "index.shtml") {
				return
			}
			//sig := fmt.Sprintf("%v", e.Request.URL)
			category := getFromChinaMap(link)
			//DebugOutput(category, title, link, sig, ChinaNewsCategory)

			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnResponse(func(r *colly.Response) {
		fileName := buildStorePageName(r.Request.URL.Hostname())
		r.Save(fileName)
	})

	c.Limit(&colly.LimitRule{
		Parallelism: SpiderParal,
		Delay:       SpiderTimeout,
	})

	c.Visit(ChinaNewsDomain)
	return titles, links, categories, SourceChinaNews
}
