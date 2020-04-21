create table news_hot_t(
	nh_id		bigint		not null	auto_increment,
	nh_title	char(128)	not null	comment "title of news",
	nh_path		char(128)	not null	comment "local path of news",
	nh_size		int			null		comment "size of news",
	nh_query	int			default 0	comment "the number of being queried",
	primary key(`nh_id`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';
