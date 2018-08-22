CREATE TABLE `fs_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sip_id` varchar(50) NOT NULL COMMENT 'SIP账号',
  `sip_password` varchar(255) NOT NULL COMMENT 'SIP密码',
  PRIMARY KEY (`id`),
  UNIQUE KEY `sip_id` (`sip_id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2513 DEFAULT CHARSET=utf8 COMMENT='SIP用户注册表';