/* FEWTWO
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef NODE_ADD
#define NODE_ADD

#include "node.h"
#ifdef USE_CUDA
    #include "../node-cuda/n_add.h"
#endif 

namespace FT{
	class NodeAdd : public Node
    {
    	public:
    	
    		NodeAdd()
       		{
    			name = "+";
    			otype = 'f';
    			arity['f'] = 2;
    			arity['b'] = 0;
    			complexity = 1;
    		}
    		
            /// Evaluates the node and updates the stack states. 
            void evaluate(const MatrixXd& X, const VectorXd& y,
                          const std::map<string, std::pair<vector<ArrayXd>, vector<ArrayXd> > >&Z, 
			              Stacks& stack);
			
            
            /// Evaluates the node symbolically
            void eval_eqn(Stacks& stack)
            {
                stack.fs.push("(" + stack.fs.pop() + "+" + stack.fs.pop() + ")");
            }
        protected:
            NodeAdd* clone_impl() const override { return new NodeAdd(*this); };  
    };
	
#ifndef USE_CUDA
    void NodeAdd::void evaluate(const MatrixXd& X, const VectorXd& y,
                          const std::map<string, std::pair<vector<ArrayXd>, vector<ArrayXd> > >&Z, 
			              Stacks& stack)
	{
		stack.f.push(limited(stack.f.pop() + stack.f.pop()));
	}
#else
void NodeAdd::void evaluate(const MatrixXd& X, const VectorXd& y,
                          const std::map<string, std::pair<vector<ArrayXd>, vector<ArrayXd> > >&Z, 
			              Stacks& stack)
	{
	    	
        Add<<< 32*NUM_SMS, 128, omp_get_thread_num() >>>(stack.dev_f, stack.idx['f'], N);
        ++stack.idx['f'];
    }
#endif
}
#endif
