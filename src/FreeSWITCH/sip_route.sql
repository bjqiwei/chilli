/*
Navicat MySQL Data Transfer

Source Server         : lingban
Source Server Version : 50556
Source Host           : 192.168.2.232:3306
Source Database       : cc

Target Server Type    : MYSQL
Target Server Version : 50556
File Encoding         : 65001

Date: 2018-07-27 16:38:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for sip_route
-- ----------------------------
DROP TABLE IF EXISTS `sip_route`;
CREATE TABLE `sip_route` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `level` int(11) DEFAULT '0' COMMENT '优先级0，优先级最高，数字越大优先级越低',
  `regex_pattern` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '.*' COMMENT '正则表达式模式匹配字符串',
  `gateway_id` int(11) DEFAULT '0' COMMENT '引用sip_gateway表中的ID，如果没有引用默认是内部呼叫',
  `name` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '路由名称',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='路由表，通过匹配被叫号码的正则表达式来决定使用哪个网关，如果没有网关使用内部呼叫。';
