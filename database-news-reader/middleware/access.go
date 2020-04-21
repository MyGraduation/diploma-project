package middleware

import (
	"io/ioutil"
	"net/http"
	"strconv"

	data "github.com/admin-news-reader/interface"
	"github.com/gin-gonic/gin"
	"github.com/mkideal/log"
)

func ResponseOK() gin.HandlerFunc {
	return func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{"message": "OK"})
	}
}

func ResponseManagerInfos() gin.HandlerFunc {
	return func(c *gin.Context) {
		managers := data.QueryManagerInfos()
		c.JSON(http.StatusOK, managers)
	}
}

func ResponseUserInfos() gin.HandlerFunc {
	return func(c *gin.Context) {
		users := data.QueryUserInfos()
		c.JSON(http.StatusOK, users)
	}
}

func ResponseNewsMetas() gin.HandlerFunc {
	return func(c *gin.Context) {
		body, _ := ioutil.ReadAll(c.Request.Body)
		offset, err := strconv.Atoi(string(body))
		if err != nil {
			log.Error("incorrect request param, offset: %v", string(body))
			c.JSON(http.StatusBadRequest, nil)
			return
		}
		cnt, metas := data.QueryNewsMetas(offset)
		res := struct {
			Count int             `json:"count"`
			Metas []data.NewsMeta `json:"metas"`
		}{
			cnt,
			metas,
		}
		c.JSON(http.StatusOK, res)
	}
}

func DeleteUserInfo() gin.HandlerFunc {
	return func(c *gin.Context) {
		body, _ := ioutil.ReadAll(c.Request.Body)
		id, err := strconv.Atoi(string(body))
		if err != nil {
			c.JSON(http.StatusBadRequest, nil)
		}
		data.DeleteUserInfo(id)
		c.JSON(http.StatusOK, "OK")
	}
}

func DeleteNewsMeta() gin.HandlerFunc {
	return func(c *gin.Context) {
		body, _ := ioutil.ReadAll(c.Request.Body)
		id, err := strconv.Atoi(string(body))
		if err != nil {
			c.JSON(http.StatusBadRequest, nil)
		}
		data.DeleteNewsMeta(id)
		c.JSON(http.StatusOK, "OK")
	}
}

func InsertNewsMeta() gin.HandlerFunc {
	return func(c *gin.Context) {
		title := c.Query("title")
		link := c.Query("link")
		category := c.Query("category")
		source := c.Query("source")
		if title == "" || link == "" || category == "" || source == "" {
			c.JSON(http.StatusBadRequest, nil)
			return
		}
		data.InsertNewsMeta(title, link, category, source)
		c.JSON(http.StatusOK, "OK")
	}
}

func SearchNewsMeta() gin.HandlerFunc {
	return func(c *gin.Context) {
		_offset := c.Query("offset")
		category := c.Query("category")
		offset, err := strconv.Atoi(_offset)
		if err != nil {
			log.Error("incorrect request param, offset: %v", _offset)
			//offset = 1
			c.JSON(http.StatusBadRequest, nil)
			return
		}
		cnt, metas := data.SearchNewsMetas(offset, category)
		res := struct {
			Count int             `json:"count"`
			Metas []data.NewsMeta `json:"metas"`
		}{
			cnt,
			metas,
		}
		c.JSON(http.StatusOK, res)
	}
}

func ValidateSuperAdmin() gin.HandlerFunc {
	return func(c *gin.Context) {
		name := c.Query("admin_name")
		passwd := c.Query("admin_passwd")

		if data.CheckAdminInfo(name, passwd) {
			c.Next()
		} else {
			c.Abort()
			c.JSON(http.StatusUnauthorized, gin.H{"message": "not super administrator"})
			return
		}
	}
}
