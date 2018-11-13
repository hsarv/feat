/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/

#include "n_exponential.h"
   	
namespace FT{

    namespace Pop{
        namespace Op{
            NodeExponential::NodeExponential(vector<double> W0)
            {
	            name = "exp";
	            otype = 'f';
	            arity['f'] = 1;
	            arity['b'] = 0;
	            complexity = 4;

                if (W0.empty())
                {
                    for (int i = 0; i < arity['f']; i++) {
                        W.push_back(r.rnd_dbl());
                    }
                }
                else
                    W = W0;
            }

            /// Evaluates the node and updates the state states. 
            void NodeExponential::evaluate(const Data& data, State& state)
            {
                state.push<double>(limited(exp(this->W[0] * state.pop<double>())));
            }

            /// Evaluates the node symbolically
            void NodeExponential::eval_eqn(State& state)
            {
                state.push<double>("exp(" + state.popStr<double>() + ")");
            }

            ArrayXd NodeExponential::getDerivative(Trace& state, int loc)
            {
                ArrayXd& x = state.get<double>()[state.size<double>()-1];
                
                switch (loc) {
                    case 1: // d/dw0
                        return x * limited(exp(this->W[0] * x));
                    case 0: // d/dx0
                    default:
                       return this->W[0] * limited(exp(W[0] * x));
                } 
            }
            
            NodeExponential* NodeExponential::clone_impl() const { return new NodeExponential(*this); }
              
            NodeExponential* NodeExponential::rnd_clone_impl() const { return new NodeExponential(); }  
        }
    }
}
