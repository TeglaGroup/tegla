#pragma once

#include <memory>
#include <quickjs.h>

#include <string>
#include <unordered_map>
#include <vector>

struct JSCallback {
	JSContext* ctx;
	JSValue	   value;
	bool	   active = true;

	~JSCallback() {
		JS_FreeValue(ctx, value);
	}
};

class ScriptingCore {
      public:
	ScriptingCore();
	~ScriptingCore();

	void RunEval(const std::string& code);

	// fires event hooks such as "onTickUpdate" etc
	void FireEvent(const std::string& eventName, int argc = 0, JSValueConst* argv = nullptr);

	JSRuntime* runtime;
	JSContext* context;

      private:
	std::unordered_map<std::string, std::vector<std::unique_ptr<JSCallback>>> hooks;

	// globals
	static JSValue js_console_log(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	static JSValue js_hook(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
};