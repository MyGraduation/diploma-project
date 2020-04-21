create table news_meta_t(
	nm_id		bigint		not null			auto_increment,
	nm_title	char(128)	not null			comment "title of news",
	nm_link		char(255)	not null			comment	"url of news on internet",
	nm_type		char(32)	default "text"		comment "text、image or video",
	nm_tag		char(32)	default "unknow"	comment "tag of news",
	nm_source	char(32)	default "unknow"	comment "source of news",
	nm_query	int			default 0			comment "the number of being queried",
	nm_time		timestamp	default now()		comment "time of getting news",
	primary key(`nm_id`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';

alter table `news_meta_t` add unique(`nm_link`);
