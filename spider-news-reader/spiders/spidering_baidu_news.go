package spiders

import (
	//"fmt"
	"sync"

	"github.com/gocolly/colly"
)

var (
	BaiduNewsCategory = make(map[string]string)
)

func pushIntoCategoryMap(key, val string) {
	if key == "/" || val == "女人" {
		return
	}
	BaiduNewsCategory[key] = val
}

func SpiderBaiduNews() (titles, links, categories []string, source string) {
	c := colly.NewCollector(
		colly.MaxDepth(SpiderDepth),
		colly.UserAgent("Opera/9.80 (Windows NT 6.1; U; zh-cn) Presto/2.9.168 Version/11.50"),
	)
	var mutex sync.RWMutex

	// 发出请求时附的回调
	c.OnRequest(func(r *colly.Request) {
		r.Headers.Set("Host", "baidu.com")
		r.Headers.Set("Connection", "keep-alive")
		r.Headers.Set("Accept", "*/*")
		r.Headers.Set("Origin", "")
		r.Headers.Set("Referer", BaiDuNewsDomain)
		r.Headers.Set("Accept-Encoding", "gzip, deflate")
		r.Headers.Set("Accept-Language", "zh-CN, zh;q=0.9")
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach("#menu a", func(i int, el *colly.HTMLElement) {
			sig := el.Attr("href")
			cat := el.Text
			pushIntoCategoryMap(sig, cat)
			e.Request.Visit(sig)
		})
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach("#col_focus a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			title := el.Text
			sig := e.Request.URL.Path
			category := BaiduNewsCategory[sig]
			//fmt.Printf("%s %s %s\n", category, title, link)
			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnHTML("body", func(e *colly.HTMLElement) {
		e.ForEach("#instant-news a", func(i int, el *colly.HTMLElement) {
			link := el.Attr("href")
			title := el.Text
			sig := e.Request.URL.Path
			category := BaiduNewsCategory[sig]
			//fmt.Printf("%s %s %s\n", category, title, link)
			appendNews(&mutex, &titles, &links, &categories, title, link, category)
		})
	})

	c.OnResponse(func(r *colly.Response) {
		fileName := buildStorePageName(r.Ctx.Get("url"))
		r.Save(fileName)
	})

	c.Limit(&colly.LimitRule{
		Parallelism: SpiderParal,
		Delay:       SpiderTimeout,
	})
	c.Visit(BaiDuNewsDomain)
	return titles, links, categories, SourceBaiduNews
}
