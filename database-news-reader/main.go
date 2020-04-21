package main

import (
	//"fmt"

	"net/http"

	"github.com/admin-news-reader/middleware"
	"github.com/gin-gonic/gin"
)

func main() {
	//fmt.Println(data.QueryNewsMetas())
	r := gin.Default()
	g := r.Group("/v1")

	g.POST("/check", middleware.ValidateSuperAdmin(), middleware.ResponseOK())
	g.GET("/check", middleware.ValidateSuperAdmin(), middleware.ResponseOK())

	g.POST("/query_news_meta", middleware.ValidateSuperAdmin(), middleware.ResponseNewsMetas())
	g.GET("/query_news_meta", middleware.ValidateSuperAdmin(), middleware.ResponseNewsMetas())

	g.POST("/query_manager_info", middleware.ValidateSuperAdmin(), middleware.ResponseManagerInfos())
	g.GET("/query_manager_info", middleware.ValidateSuperAdmin(), middleware.ResponseManagerInfos())

	g.POST("/query_user_info", middleware.ValidateSuperAdmin(), middleware.ResponseUserInfos())
	g.GET("/query_user_info", middleware.ValidateSuperAdmin(), middleware.ResponseUserInfos())

	g.POST("/delete_user_info", middleware.ValidateSuperAdmin(), middleware.DeleteUserInfo())
	g.GET("/delete_user_info", middleware.ValidateSuperAdmin(), middleware.DeleteUserInfo())

	g.POST("/delete_news_meta", middleware.ValidateSuperAdmin(), middleware.DeleteNewsMeta())
	g.GET("/delete_news_meta", middleware.ValidateSuperAdmin(), middleware.DeleteNewsMeta())

	g.POST("/insert_news_meta", middleware.InsertNewsMeta())
	g.GET("/insert_news_meta", middleware.InsertNewsMeta())

	g.POST("/search_news_meta", middleware.SearchNewsMeta())
	g.GET("/search_news_meta", middleware.SearchNewsMeta())

	g.StaticFS("/static/", http.Dir("./static"))
	err := r.Run()
	if err != nil {
		return
	}
}
