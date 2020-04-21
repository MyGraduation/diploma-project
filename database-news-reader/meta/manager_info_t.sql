create table manager_info_t(
		mi_id			bigint		not null		auto_increment,
		mi_mail 		char(64)	not null		comment "manager e_mail",
		mi_passwd		char(32) 	not null		comment "manager passwd",
		mi_level		int			default 2		comment "level of power",
		primary key(`mi_id`),
		index(`mi_mail`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';
