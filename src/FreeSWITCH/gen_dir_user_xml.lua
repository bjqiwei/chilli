
local dbh = freeswitch.Dbh("freeswitch","root","unitcc")

local req_domain = params:getHeader("domain")
local req_key    = params:getHeader("key")
local req_user   = params:getHeader("user")
local req_password   = params:getHeader("pass")

local req_callgroup=params:getHeader("pass")

if req_user == nil then
    return
end

if dbh:connected() == false then
  freeswitch.consoleLog("notice", "gen_dir_user_xml.lua cannot connect to database\n")
  return
end

dbh:query("select sip_password from sip_users where sip_id='"..req_user.."'",function(row)
        req_password= row.sip_password
end);


req_callgroup=""


if req_domain ~= nil and req_key~=nil and req_user~=nil and req_password~=nil then
    XML_STRING =
    [[<?xml version="1.0" encoding="UTF-8" standalone="no"?>
    <document type="freeswitch/xml">
      <section name="directory">
        <domain name="]]..req_domain..[[">
          <params>
        <param name="dial-string"
        value="{presence_id=${dialed_user}@${dialed_domain}}${sofia_contact(${dialed_user}@${dialed_domain})}"/>
      
    </params>
       <groups>
        <group name="default">
          <users>
            <user id="]] ..req_user..[[">
              <params>
            <param name="password" value="]]..req_password..[["/>
            <param name="vm-password" value="]]..req_password..[["/>
	        </params>
              <variables>
                 <variable name="toll_allow" value="domestic,international,local"/>
                 <variable name="accountcode" value="]] ..req_user..[["/>
                 <variable name="user_context" value="default"/>
                 <variable name="directory-visible" value="true"/>
              </variables>
            </user>
          </users>
        </group>

          </groups>
        </domain>
      </section>
    </document>]]
end
