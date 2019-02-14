#ifndef TL_RANGES_COPY_HPP
#define TL_RANGES_COPY_HPP


#include <algorithm>		// std::copy
#include <execution>		// std::is_execution_policy_v
#include <iterator>			// std::begin, std::end
#include <type_traits>		// std::decay_t, std::enable_if_t
#include <utility>			// std::forward


namespace tl::ranges {

	/* Copies the elements of src to dst.
		This simply provides a range-based interface for std::copy, see that documentation for exact semantics. */
	template<class InputRange, class OutputRange>
	void copy(InputRange&& src, OutputRange&& dst)
	{
		std::copy(std::begin(src), std::end(src), std::begin(dst));
	}


	/* Copies the elements of src to dst, executed according to exec_policy.
		This simply provides a range-based interface for std::copy, see that documentation for exact semantics. */
	template<class ExecutionPolicy, class InputRange, class OutputRange>
	std::enable_if_t<std::is_execution_policy_v<std::decay_t<ExecutionPolicy>>, void>
		copy(ExecutionPolicy&& exec_policy, InputRange&& src, OutputRange&& dst)
	{
		std::copy(std::forward<ExecutionPolicy>(exec_policy), std::begin(src), std::end(src), std::begin(dst));
	}

}


#endif
