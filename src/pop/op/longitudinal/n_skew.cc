/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/

#include "n_skew.h"
#include "../../../util/utils.h"

namespace FT{

    namespace Pop{
        namespace Op{
            NodeSkew::NodeSkew()
            {
                name = "skew";
	            otype = 'f';
	            arity['z'] = 1;
	            complexity = 3;
            }

            /// Evaluates the node and updates the state states. 
            void NodeSkew::evaluate(const Data& data, State& state)
            {
                ArrayXd tmp(state.z.top().first.size());
                
                int x;
                
                for(x = 0; x < state.z.top().first.size(); x++)
                    tmp(x) = skew(limited(state.z.top().first[x]));
                    
                state.z.pop();

                state.push<double>(tmp);
                
            }

            /// Evaluates the node symbolically
            void NodeSkew::eval_eqn(State& state)
            {
                state.push<double>("skew(" + state.zs.pop() + ")");
            }

            NodeSkew* NodeSkew::clone_impl() const { return new NodeSkew(*this); }

            NodeSkew* NodeSkew::rnd_clone_impl() const { return new NodeSkew(); } 
        }
    }
}
