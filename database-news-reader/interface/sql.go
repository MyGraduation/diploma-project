package interface

import (
	"fmt"

	_ "github.com/go-sql-driver/mysql"
	"github.com/mkideal/log"
)

func InsertNewsMeta(title, link, category, source string) error {
	stmt := "insert into news_meta_t(nm_title, nm_link, nm_tag, nm_source)"
	stmt += fmt.Sprintf("values('%s', '%s', '%s', '%s')", title, link, category, source)
	return Insert(stmt)
}

func CheckAdminInfo(mail, passwd string) bool {
	if mail == "" || passwd == "" {
		return false
	}
	managers := QueryManagerInfos()
	for _, manager := range managers {
		if manager.Mail == mail && manager.Passwd == passwd {
			return true
		}
	}
	return false
}

func DeleteUserInfo(id int) {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	stmt, err := SQLHandler.Prepare("delete from user_info_t where ui_id=?")
	if err != nil {
		log.Warn("fail to delete user whose id is %d, err: %v", id, err)
		return
	}
	if _, err = stmt.Exec(id); err != nil {
		log.Warn("fail to delete user whose id is %d", id)
	}
	log.Warn("delete user %v successfully", id)
}

func DeleteNewsMeta(id int) {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	stmt, err := SQLHandler.Prepare("delete from news_meta_t where nm_id=?")
	if err != nil {
		log.Warn("fail to delete news whose id is %d, err: %v", id, err)
		return
	}
	if _, err = stmt.Exec(id); err != nil {
		log.Warn("fail to delete news whose id is %d", id)
	}
	log.Warn("delete news %v successfully", id)
}

func QueryNewsMetas(offset int) (int, []NewsMeta) {
	if offset == 0 {
		offset = 1
	}
	return selectNewsMetas(offset, "")
}

func SearchNewsMetas(offset int, category string) (int, []NewsMeta) {
	if offset == 0 {
		offset = 1
	}
	return selectNewsMetas(offset, category)
}

func selectNewsMetas(offset int, category string) (int, []NewsMeta) {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	news := []NewsMeta{}
	cnt := 0

	var stmt string
	if category == "" {
		stmt = "select count(*) from news_meta_t"
	} else {
		stmt = fmt.Sprintf("select count(*) from news_meta_t where nm_tag='%s'", category)
	}
	log.Info("start to execute sql statement: %v", stmt)
	row, err := SQLHandler.Query(stmt)
	defer func() {
		if row != nil {
			row.Close()
		}
	}()
	if err != nil {
		log.Warn("Query failed, err: %v", err)
		return 0, nil
	}
	for row.Next() {
		if err = row.Scan(&cnt); err != nil {
			log.Warn("Scan failed, err: %v", err)
			return 0, nil
		}
	}

	start := (offset - 1) * PageLimit
	if category == "" {
		stmt = fmt.Sprintf("select * from news_meta_t order by nm_id desc limit %d, %d", start, PageLimit)
	} else {
		stmt = fmt.Sprintf("select * from news_meta_t where nm_tag='%s' order by nm_id desc limit %d, %d", category, start, PageLimit)
	}
	log.Info("start to execute sql statement: %v", stmt)
	rows, err := SQLHandler.Query(stmt)
	defer func() {
		if rows != nil {
			rows.Close()
		}
	}()
	if err != nil {
		log.Warn("Query failed, err: %v", err)
		return 0, nil
	}
	for rows.Next() {
		oneNews := NewsMeta{}
		err = rows.Scan(&oneNews.ID, &oneNews.Title, &oneNews.Link, &oneNews.Type, &oneNews.Tag, &oneNews.Source, &oneNews.Query, &oneNews.Time)
		if err != nil {
			log.Warn("Scan failed, err: %v", err)
			return 0, nil
		}
		news = append(news, oneNews)
	}

	return cnt, news
}

func QueryUserInfos() []UserInfo {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	users := []UserInfo{}
	rows, err := SQLHandler.Query("select * from user_info_t")
	defer func() {
		if rows != nil {
			rows.Close()
		}
	}()

	if err != nil {
		log.Warn("Query failed, err: %v", err)
		return nil
	}
	for rows.Next() {
		user := UserInfo{}
		err = rows.Scan(&user.ID, &user.Mail, &user.Name, &user.Sex, &user.Age, &user.Photo, &user.Area, &user.Tag)
		if err != nil {
			log.Warn("Scan failed, err: %v", err)
			return nil
		}
		users = append(users, user)
	}
	return users
}

func QueryManagerInfos() []ManagerInfo {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	managers := []ManagerInfo{}
	rows, err := SQLHandler.Query("select * from manager_info_t")
	defer func() {
		if rows != nil {
			rows.Close()
		}
	}()

	if err != nil {
		log.Warn("Query failed, err: %v", err)
		return nil
	}
	for rows.Next() {
		manager := ManagerInfo{}
		err = rows.Scan(&manager.ID, &manager.Mail, &manager.Passwd, &manager.Level)
		if err != nil {
			log.Warn("Scan failed, err: %v", err)
			return nil
		}
		managers = append(managers, manager)
	}
	return managers
}

func Insert(sql string) error {
	SQLMutex.Lock()
	defer SQLMutex.Unlock()
	_, err := SQLHandler.Exec(sql)
	if err != nil {
		log.Warn("insert failed, sql: %v, err:%v", sql, err)
		return err
	}
	return nil
}


/*
func main() {
	InitDB()
	fmt.Println(QueryManagerInfos())
}

insert into manager_info_t(mi_mail, mi_passwd) values
("18846135971@163.com", "123456");

insert into user_info_t(ui_mail, ui_name, ui_sex, ui_age, ui_photo, ui_area, ui_tag) values
("18846135971@163.com", "wanglongfei", 1, 23, "", "四川", "军事|政治|经济|科技")

insert into user_info_t(ui_id, ui_mail, ui_name, ui_sex, ui_age, ui_photo, ui_area, ui_tag) values
(2, "12345678910@qq.com", "felix", 1, 20, "", "北京", "电影|音乐|美食|运动")

insert into user_info_t(ui_id, ui_mail, ui_name, ui_sex, ui_age, ui_photo, ui_area, ui_tag) values
(3, "98765432101@bytedance.com", "王龙飞", 1, 23, "", "四川", "网络|游戏|程序|财经")

insert into user_info_t(ui_mail, ui_name, ui_sex, ui_age, ui_photo, ui_area, ui_tag) values
("18846135971@163.com", "wanglongfei", 1, 23, "", "四川", "军事|政治|经济|科技")

insert into news_meta_t(nm_title, nm_link, nm_type) values
("以生态留人靠文化引人", "http://opinion.people.com.cn/n1/2020/0121/c1003-31557596.html", "text")

insert into news_meta_t(nm_title, nm_link, nm_type) values
("部委这一年:司法行政事业迈上新台阶", "http://legal.people.com.cn/n1/2020/0121/c42510-31558881.html", "text")
*/
