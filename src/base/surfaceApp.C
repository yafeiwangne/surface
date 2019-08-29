#include "surfaceApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<surfaceApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

surfaceApp::surfaceApp(InputParameters parameters) : MooseApp(parameters)
{
  surfaceApp::registerAll(_factory, _action_factory, _syntax);
}

surfaceApp::~surfaceApp() {}

void
surfaceApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"surfaceApp"});
  Registry::registerActionsTo(af, {"surfaceApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
surfaceApp::registerApps()
{
  registerApp(surfaceApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
surfaceApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  surfaceApp::registerAll(f, af, s);
}
extern "C" void
surfaceApp__registerApps()
{
  surfaceApp::registerApps();
}
