package interface

import (
	"database/sql"
	"sync"
)

const (
	DBName    = "sys_news_reader"
	PageLimit = 35
)

var (
	SQLHandler *sql.DB
	SQLMutex   sync.RWMutex
)

type ManagerInfo struct {
	ID     int    `json:"id"`
	Mail   string `json:"mail"`
	Passwd string `json:"passwd"`
	Level  string `json:"level"`
}

type UserInfo struct {
	ID    int    `json:"id"`
	Mail  string `json:"mail"`
	Name  string `json:"name"`
	Tag   string `json:"tag"`
	Sex   int    `json:"sex"`
	Age   int    `json:"age"`
	Photo string `json:"photo"`
	Area  string `json:"area"`
}

type NewsMeta struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Link   string `json:"link"`
	Type   string `json:"type"`
	Tag    string `json:"tag"`
	Source string `json:"source"`
	Query  int    `json:"query"`
	Time   string `json:"tsmp"`
}

func init() {
	dsn := "root@tcp(127.0.0.1:3306)/" + DBName
	SQLHandler, _ = sql.Open("mysql", dsn)
}
