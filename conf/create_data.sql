use fcdeduction;

insert into de_user(tnt_inst_id, user_id, user_name, user_type, gmt_create, gmt_modified) values("FINC0001","00000001","Ramsay","1",now(6),now(6));

insert into de_ar(tnt_inst_id, ar_number, ar_name, ar_version, properties, memo, gmt_create, gmt_modified) VALUES ("FINC0001","00000001","扣费合约","1","","备注",now(6),now(6));

insert into de_ident(tnt_inst_id, ident_id, user_id, ident_type, ident_key, ident_value, gmt_create, gmt_modified) values ("FINC0001","457316782383050776","00000001","1","ramsayleung@gmail.com","229717b044cdf2210e6a398808e97f15bcd6dd528780dfab3428ccbcea78e805",now(6),now(6));

insert into de_prod(tnt_inst_id, pd_code, pd_name, pd_desc, pd_org_name, memo, gmt_create, gmt_modified) values ("FINC0001", "00000001","摩拜单车微信免密支付","摩拜单车微信免密支付","摩拜单车","",now(6),now(6));