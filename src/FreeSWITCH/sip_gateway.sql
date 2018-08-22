/*
Navicat MySQL Data Transfer

Source Server         : lingban
Source Server Version : 50556
Source Host           : 192.168.2.232:3306
Source Database       : cc

Target Server Type    : MYSQL
Target Server Version : 50556
File Encoding         : 65001

Date: 2018-07-27 16:40:41
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for sip_gateway
-- ----------------------------
DROP TABLE IF EXISTS `sip_gateway`;
CREATE TABLE `sip_gateway` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `ip` varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '网关IP地址',
  `port` int(11) DEFAULT '5060' COMMENT '网关端口',
  `name` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '网关名称',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='网关配置表，配置外部SIP网关';
