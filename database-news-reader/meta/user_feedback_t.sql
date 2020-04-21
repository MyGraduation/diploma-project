create table user_feedback_t (
		uf_id			bigint		not null		auto_increment,
		uf_mail 		char(64)	not null		comment "user e_mail",
		uf_time			timestamp	default now()	comment "time of feedbacking",
		uf_done			int			default 0		comment "has manager deal",
		primary key(`uf_id`)

)ENGINE=InnoDB DEFAULT CHARSET='utf8';
