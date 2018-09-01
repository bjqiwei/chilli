#include "JSContext.h"
#include <js/Initialization.h>
#include <mozilla/Maybe.h>
#include <jswrapper.h>
#include <js/Conversions.h>
#include <jsperf.h>
#include "../../common/stringHelper.h"
#include <log4cplus/loggingmacros.h>


namespace fsm
{
namespace env
{

	static const size_t gStackChunkSize = 4096;

	JsContext::JsContext(::JSRuntime * rt, const std::string &sessionid, Evaluator * eval,Context * _parent)
		:Context(eval, _parent), m_strSessionID(sessionid), m_jsrt(rt)
	{
		log =  log4cplus::Logger::getInstance("fsm.JsContext");
		LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ",new a fsm.env.JsContext object:" << this << " parent:" << parent);
		
		InitializeInstanceFields();
		//LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ",new a fsm.env.JsContext object finish.");
	}

	void JsContext::setVar(const std::string & name, const Json::Value & value)
	{
		JSAutoRequest ar(this->m_jsctx);
		JS::RootedObject  obj(this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);
		JS::RootedValue val(this->m_jsctx,JsonValueToJsval(value));
		
		std::string _name = name;
		std::string::size_type pos;
		while ((pos = _name.find_first_of(".")) != std::string::npos)
		{
			std::string objName = _name.substr(0,pos);
			_name = _name.substr(pos + 1);
			JS::RootedValue rval(this->m_jsctx);

			if (JS_GetProperty(m_jsctx, obj, objName.c_str(), &rval)){
				
				if (rval.isObject()){
					obj.set(&rval.toObject());
				}
				else {

					JS::RootedObject _object(m_jsctx, JS_NewObject(m_jsctx, nullptr));
					if (!_object) {
						LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_NewObject " << objName);
						return;
					}

					if (!JS_DefineProperty(m_jsctx, obj, objName.c_str(), _object, JSPROP_ENUMERATE)) {
						LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_DefineProperty " << objName);
						return;
					}
					obj = _object;
				}
			}
			else {
				LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_GetProperty " << objName);
				return;
			}
		}


		//std::string out = value.toStyledString();
		//helper::string::trim(out);
		//LOG4CPLUS_TRACE(log, "." + m_strSessionID, ",set "<< (va==fsm::globalObject? "global.":"_event.") << name << "=" << out);

		if (!JS_DefineProperty(m_jsctx, obj, _name.c_str(), val, JSPROP_READONLY | JSPROP_ENUMERATE)) {
			LOG4CPLUS_WARN(log, "." + m_strSessionID, ",define "<< " property " << name << " failed.");
		}

	}

	Json::Value JsContext::getVar(const std::string &name)
	{
		JSAutoRequest ar(this->m_jsctx);
		JS::RootedObject  obj(this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);

		JS::RootedValue rval(this->m_jsctx);

		bool has = false;
		if (JS_AlreadyHasOwnProperty(m_jsctx, obj, name.c_str(), &has) && has) {
			bool status = JS_GetProperty(m_jsctx, obj, name.c_str(), &rval);
			if (status == true) {
				return JsvalToJsonValue(rval);

			}
		}
		return Json::Value();
	}

	void JsContext::deleteVar(const std::string & name)
	{
		JSAutoRequest ar = JSAutoRequest(this->m_jsctx);
		JS::RootedObject obj (this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);

		//LOG4CPLUS_TRACE(log, "." + m_strSessionID, ",delete "<< (va==fsm::globalObject? "global.":"_event.") << name );

		if(!JS_DeleteProperty(m_jsctx, obj, name.c_str())){
			LOG4CPLUS_ERROR(log, "." + m_strSessionID, ", delete Var " << name << " failed.");
		}
	
	}


	Context *JsContext::getParent()
	{
		LOG4CPLUS_TRACE(log, "." + m_strSessionID, ",getParent:" << parent);
		return parent;
	}


	Json::Value JsContext::eval(const std::string &expr,const std::string &filename, unsigned int line)
	{
		//JS_DumpNamedRoots(JS_GetRuntime(ctx), JsGlobal::dumpRoot, NULL);
		
		JSAutoRequest ar = JSAutoRequest(this->m_jsctx);
		JS::RootedObject  obj(this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);

		JS::CompileOptions options(this->m_jsctx);
		options.setFileAndLine(filename.c_str(), line);

		JS::RootedValue rv(this->m_jsctx);
		if (JS::Evaluate(this->m_jsctx, options, expr.c_str(), expr.length(), &rv)) {
			return JsvalToJsonValue(rv);
		}
		return Json::Value();
	}

	bool JsContext::evalCond(const std::string &expr,const std::string &filename, unsigned int line)
	{

		JSAutoRequest ar = JSAutoRequest(this->m_jsctx);
		JS::RootedObject  obj(this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);

		JS::CompileOptions options(this->m_jsctx);
		options.setFileAndLine(filename.c_str(), line);

		JS::RootedValue rv(this->m_jsctx);
		if (JS::Evaluate(this->m_jsctx, options, expr.c_str(), expr.length(), &rv)) {
			return JS::ToBoolean(rv);
		}
		
		return false;
	}

	void JsContext::ExecuteFile(const std::string &fileName)
	{
		JSAutoRequest ar = JSAutoRequest(this->m_jsctx);
		JS::RootedObject  obj(this->m_jsctx, *this->m_global);
		JSAutoCompartment ac(this->m_jsctx, *this->m_global);

		JS::CompileOptions options(this->m_jsctx);

		JS::RootedValue rv(this->m_jsctx);
		if (JS::Evaluate(this->m_jsctx, options,fileName.c_str(), &rv)) {
			return ;
		}
		return ;
	}
	static bool
		global_enumerate(JSContext* cx, JS::HandleObject obj)
	{
#ifdef LAZY_STANDARD_CLASSES
		return JS_EnumerateStandardClasses(cx, obj);
#else
		return true;
#endif
	}

	static bool
		global_resolve(JSContext* cx, JS::HandleObject obj, JS::HandleId id, bool* resolvedp)
	{
#ifdef LAZY_STANDARD_CLASSES
		if (!JS_ResolveStandardClass(cx, obj, id, resolvedp))
			return false;
#endif
		return true;
	}

	static bool
		global_mayResolve(const JSAtomState& names, jsid id, JSObject* maybeObj)
	{
		return JS_MayResolveStandardClass(names, id, maybeObj);
	}

	static const JSClass global_class = {
		"global", JSCLASS_GLOBAL_FLAGS,
		nullptr, nullptr, nullptr, nullptr,
		global_enumerate, global_resolve, global_mayResolve,
		nullptr,
		nullptr, nullptr, nullptr,
		JS_GlobalObjectTraceHook
	};

	void JsContext::InitializeInstanceFields()
	{
		
		m_jsctx = JS_NewContext(m_jsrt, gStackChunkSize);
		if (m_jsctx == NULL){
			LOG4CPLUS_ERROR(log, "." + m_strSessionID, ",JS_NewContext error.");
			throw std::logic_error("JS_NewContext error.");
		}

		/* Enter a request before running anything in the context */
		JSAutoRequest ar(m_jsctx);
		JS_SetContextPrivate(m_jsctx, this);

		// Create the global object and a new compartment.

		JS::CompartmentOptions options;
		options.setVersion(JSVERSION_DEFAULT);
		options.setInvisibleToDebugger(true);
		
		m_global = new JS::RootedObject(m_jsctx, JS_NewGlobalObject(m_jsctx, &global_class, nullptr,
			JS::DontFireOnNewGlobalHook, options));

		if (!(*m_global))
			throw std::logic_error("JS_NewGlobalObject error.") ;

		// Enter the new global object's compartment.
		JSAutoCompartment ac(m_jsctx, *m_global);

		/* Populate the global object with the standard globals, like Object and Array. */
		if (!JS_InitStandardClasses(m_jsctx, *m_global))
			throw std::logic_error("JS_InitStandardClasses error.");

#ifdef JS_HAS_CTYPES
		if (!JS_InitCTypesClass(m_jsctx, global))
			throw std::logic_error("JS_InitCTypesClass error.");
#endif
		//if (!JS_InitReflectParse(m_jsctx, *m_global))
			//throw std::logic_error("JS_InitReflectParse error.");

		//if (!JS_DefineDebuggerObject(m_jsctx, *m_global))
			//throw std::logic_error("JS_DefineDebuggerObject error.");

		//if (!JS::RegisterPerfMeasurement(m_jsctx, *m_global))
			//throw std::logic_error("RegisterPerfMeasurement error.");

		bool succeeded;
		if (!JS_SetImmutablePrototype(m_jsctx, *m_global, &succeeded))
			throw std::logic_error("JS_SetImmutablePrototype error.");

		JS_FireOnNewGlobalObject(m_jsctx, *m_global);
	}

	JsContext::~JsContext()
	{
		//LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ",Destroy SpiderMonkey Context." );
		if (m_global)
			delete m_global;

		if (m_jsctx) 
			JS_DestroyContext(m_jsctx);

		LOG4CPLUS_DEBUG(log, "." + m_strSessionID, ",destructioned a fsm.env.JsContext object:" << this );
	}

	JS::Value JsContext::JsonValueToJsval(const Json::Value &value)const
	{
		JS::Value val = JS::NullValue();
		if (value.isBool()){
			val.setBoolean(value.asBool());

		}else if(value.isInt()){
			val.setInt32(value.asInt());
		}
		else if (value.isDouble()) {
			val.setDouble(value.asDouble());

		}else if (value.isNull()){
			val.setNull();

		}else if (value.isString())
		{
			val.setString(JS_NewStringCopyZ(this->m_jsctx, value.asCString()));
		}else if (value.isUInt())
		{
			val.setPrivateUint32(value.asUInt());
		}
		else if (value.isObject())
		{
			JS::RootedObject  obj(this->m_jsctx, JS_NewObject(m_jsctx, nullptr));
		
			if (!obj) {
				LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_NewObject " << value.toStyledString());
				return val;
			}

			for (auto & it : value.getMemberNames()) {
				
				JS::RootedValue  val2(this->m_jsctx,JsonValueToJsval(value[it]));
			
				if(!JS_DefineProperty(this->m_jsctx, obj, it.c_str(), val2, JSPROP_ENUMERATE))
				{
					LOG4CPLUS_WARN(log, "." + m_strSessionID, ",define " << " property " << it << " failed.");
				}
			}

			val.setObject(*obj);
		}
		else if (value.isArray())
		{
			JS::RootedObject _array(m_jsctx, JS_NewArrayObject(m_jsctx, value.size()));
			if (!_array) {
				LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_NewArrayObject " << value.toStyledString());
				return val;
			}
			for (uint32_t i = 0; i < value.size(); i++)
			{
				JS::RootedValue val2(this->m_jsctx, JsonValueToJsval(value[i]));
				JS_DefineElement(m_jsctx, _array, i, val2, JSPROP_ENUMERATE);
			}
			val.setObject(*_array);
		}
		return val;
	}

	Json::Value JsContext::JsvalToJsonValue(const JS::Value &value)const
	{
		
		if (value.isBoolean()){
			return value.toBoolean();

		}
		else if (value.isDouble()){
			return value.toDouble();

		}
		else if(value.isInt32()){
			return value.toInt32();

		}
		else if (value.isNullOrUndefined()){
			return Json::Value();

		}
		else if (value.isNumber())
		{
			return value.toNumber();
			
		}
		else if (value.isString())
		{
			JSAutoByteString bytes(this->m_jsctx, value.toString());
			if (bytes.ptr()) {
				return bytes.ptr();
			}
		}
		else if (value.isObject())
		{
			Json::Value result;
			JS::RootedObject obj(this->m_jsctx, value.toObjectOrNull());
			JS::Rooted<JS::IdVector> props(this->m_jsctx, JS::IdVector(this->m_jsctx));


			if (!JS_Enumerate(this->m_jsctx, obj, &props)) {
				LOG4CPLUS_ERROR(log, "." + m_strSessionID, "JS_Enumerate error");
				return result;
			}

			size_t length = props.length();
			for (size_t i = 0; i < length; i++) {
				JS::RootedValue v(this->m_jsctx);

				if (JS_GetPropertyById(this->m_jsctx, obj, props[i], &v)) {
				
					if (JSID_IS_STRING(props[i])) {
						JSString *str = JSID_TO_STRING(props[i]);
						if (str) {
							JSAutoByteString bytes(this->m_jsctx, str);
							if (bytes.ptr()) {
								Json::Value val = JsvalToJsonValue(v);
								result[bytes.ptr()] = val;
							}
						}
					}
					else if(JSID_IS_INT(props[i])) {
						result[JSID_TO_INT(props[i])] = JsvalToJsonValue(v);

					}
				}

			}

			return result;
		}
		return Json::Value();
	}
}
}
