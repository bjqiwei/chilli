/*
Navicat MySQL Data Transfer

Source Server         : cti
Source Server Version : 50505
Source Host           : 192.168.1.250:3306
Source Database       : cti

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2017-12-02 01:15:10
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for agentlogin
-- ----------------------------
DROP TABLE IF EXISTS `agentlogin`;
CREATE TABLE `agentlogin` (
  `Id` char(64) NOT NULL,
  `AgentID` char(10) NOT NULL,
  `Extension` char(10) NOT NULL,
  `LoginTime` datetime NOT NULL,
  `LogoutTime` datetime DEFAULT NULL,
  PRIMARY KEY (`Id`),
  KEY `agentid` (`AgentID`),
  KEY `logintime` (`LoginTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for calldetail
-- ----------------------------
DROP TABLE IF EXISTS `calldetail`;
CREATE TABLE `calldetail` (
  `CallID` char(64) NOT NULL,
  `ConnectID` char(64) NOT NULL,
  `Direction` int(1) DEFAULT '0',
  `Caller` char(20) DEFAULT NULL,
  `AgentID` char(10) DEFAULT NULL,
  `Called` char(20) DEFAULT NULL,
  `StartTime` datetime NOT NULL,
  `RingingTime` datetime DEFAULT NULL,
  `AnswerTime` datetime DEFAULT NULL,
  `EndTime` datetime DEFAULT NULL,
  PRIMARY KEY (`StartTime`,`CallID`,`ConnectID`),
  KEY `agentid` (`AgentID`),
  KEY `starttime` (`StartTime`),
  KEY `caller` (`Caller`),
  KEY `called` (`Called`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
