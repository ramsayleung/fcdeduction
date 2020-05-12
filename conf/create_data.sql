use fcdeduction;

# 通过保证插入成功.
delete from de_user where tnt_inst_id = "FINC0001" and user_id in ("00000001","00000002");

insert into de_user(tnt_inst_id, user_id, user_name, user_type, gmt_create, gmt_modified) values("FINC0001","00000001","Ramsay","1",now(6),now(6));

insert into de_user(tnt_inst_id, user_id, user_name, user_type, gmt_create, gmt_modified) values("FINC0001","00000002","Beyond","1",now(6),now(6));

delete from de_ar where tnt_inst_id = "FINC0001" and ar_number = "457681411894423554";

insert into de_ar(tnt_inst_id, ar_number, ar_name, ar_version, properties, memo, gmt_create, gmt_modified) VALUES ("FINC0001","457681411894423554","扣费合约","1","","备注",now(6),now(6));

delete from de_ident where tnt_inst_id = "FINC0001" and ident_id in( "457316782383050776","457691422632718338");

insert into de_ident(tnt_inst_id, ident_id, user_id, ident_type, ident_key, ident_value, gmt_create, gmt_modified) values ("FINC0001","457316782383050776","00000001","1","ramsayleung@gmail.com","229717b044cdf2210e6a398808e97f15bcd6dd528780dfab3428ccbcea78e805",now(6),now(6));

insert into de_ident(tnt_inst_id, ident_id, user_id, ident_type, ident_key, ident_value, gmt_create, gmt_modified) values ("FINC0001","457691422632718338","00000002","1","xixihaha@outlook.com","1a7f75e766c4411c721428b98d0e3d2d0369f6b1ef70cdf88253c7d6a0fee88f",now(6),now(6));

delete from de_prod where tnt_inst_id = "FINC0001" and pd_code in ("457680430309847040","457680430309847041","457680430309847042");

insert into de_prod(tnt_inst_id, pd_code, pd_name, pd_desc, pd_org_name, memo, gmt_create, gmt_modified) values ("FINC0001", "457680430309847040","摩拜单车微信免密支付","摩拜单车微信免密支付","摩拜单车","",now(6),now(6));

insert into de_prod(tnt_inst_id, pd_code, pd_name, pd_desc, pd_org_name, memo, gmt_create, gmt_modified) values ("FINC0001", "457680430309847041","上海公共交通微信免密支付","公共免密支付","上海公共交通乘车码","",now(6),now(6));

insert into de_prod(tnt_inst_id, pd_code, pd_name, pd_desc, pd_org_name, memo, gmt_create, gmt_modified) values ("FINC0001", "457680430309847042","测试产品","这是个测试产品","测试产品公司","",now(6),now(6));

