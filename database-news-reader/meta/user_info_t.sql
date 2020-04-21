create table user_info_t(
		ui_id			bigint		not null		auto_increment,
		ui_mail 		char(64)	not null		comment "user e_mail",
		ui_name 		char(32) 	not null		comment "user name",
		ui_sex			char(32) 	null			comment "user sex",
		ui_age			int		    null			comment "user age",
		ui_photo		char(32)	null			comment "head of user appear",
		ui_area			char(16)	null			comment "user location",
		ui_tag			char(255)	null			comment "interest of user",
		primary key(`ui_id`),
		index(`ui_mail`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';

