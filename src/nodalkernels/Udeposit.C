//doing the RHS of du/dt=v-u

#include "Udeposit.h"
#include "Function.h"
#include "NodalKernel.h"
registerMooseObject("SurfaceDeposit1App", Udeposit);

template <>
InputParameters
validParams<Udeposit>()
{
  InputParameters params = validParams<NodalKernel>();
  params.addCoupledVar("coupled_var", "	Choose the variable you want to couple");
  params.addParam<Real>("K_O", 1.0, "standard reaction rate");
  params.addRequiredParam<FunctionName>("Exp_1", "Exp_1 term in Butler Volmer Eq");
  params.addRequiredParam<FunctionName>("Exp_2", "Exp_2 term in Butler Volmer Eq");
  return params;
}

Udeposit::Udeposit(const InputParameters & parameters)
  : NodalKernel(parameters), 
    _couple_var(coupledValue("coupled_var")),
    _couple_var_offjac(coupled("coupled_var")),
    _K_O(getParam<Real>("K_O")),
    _func_1(getFunction("Exp_1")),
    _func_2(getFunction("Exp_2"))
{
}


Real
Udeposit::computeQpResidual()
{
    return  -_K_O*(_couple_var[_qp]*_func_1.value(_t, *_current_node) - _u[_qp]*_func_2.value(_t, *_current_node));
}


Real
Udeposit::computeQpJacobian()
{
  return _K_O*_func_2.value(_t, *_current_node);
}

Real
Udeposit::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _couple_var_offjac)
    return -_K_O*_func_1.value(_t, *_current_node);
  else
    return 0;
}
