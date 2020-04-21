create table user_state_t(
		us_mail 		char(64)	not null		comment "user e_mail",
		us_passwd		char(32) 	not null		comment "user passwd",
		us_state		int			not null		comment "user state",
		us_member		int		    default 0		comment "news reader member",
		us_time			timestamp   default now()	comment "time of log in",
		primary key(`us_mail`),
		index(`us_mail`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';
