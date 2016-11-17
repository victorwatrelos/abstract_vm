#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include <vector>
# include "Instruction.hpp"

class Software
{
	public:
		Software(void);
		Software(const Software &obj);
		Software &operator=(const Software &p);
		void	addIns(Instruction ins);
		virtual ~Software(void);
		void	disp(void);
	private:
		std::vector<Instruction>	_program;
};
#endif
