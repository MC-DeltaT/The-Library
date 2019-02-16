#ifndef TL_RANGES_REDUCE_HPP
#define TL_RANGES_REDUCE_HPP


#include <execution>		// std::is_execution_policy_v
#include <iterator>			// std::begin, std::end
#include <numeric>			// std::reduce
#include <type_traits>		// std::decay_t, std::enable_if_t
#include <utility>			// std::forward


namespace tl::ranges {

	/* Reduces the elements of range, along with init, over op.
		This simply provides a range-based interface for std::reduce, see that documentation for exact semantics. */
	template<class InputRange, typename T, typename BinaryOperation>
	T reduce(InputRange&& range, T init, BinaryOperation op)
	{
		return std::reduce(std::begin(range), std::end(range), init, op);
	}


	/* Reduces the elements of range, along with init, over op, executed according to exec_policy.
		This simply provides a range-based interface for std::reduce, see that documentation for exact semantics. */
	template<class ExecutionPolicy, class InputRange, typename T, typename BinaryOperation>
	std::enable_if_t<std::is_execution_policy_v<std::decay_t<ExecutionPolicy>>, T>
		reduce(ExecutionPolicy&& exec_policy, InputRange&& range, T init, BinaryOperation op)
	{
		return std::reduce(std::forward<ExecutionPolicy>(exec_policy), std::begin(range), std::end(range), init, op);
	}

}


#endif
