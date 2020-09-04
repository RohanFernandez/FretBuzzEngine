#pragma once

namespace FRETBUZZ
{
	class  IFSM
	{
	protected:
		std::string m_strStateName;

	public:
		virtual void OnStateEnter() = 0
		{
			std::cout << "State Entered :: '" << m_strStateName << "'\n";
		}

		virtual void OnStateExit() = 0
		{
			std::cout << "State Exited :: '" << m_strStateName << "'\n";
		}

		inline const std::string getStateName() const
		{
			return m_strStateName;
		}

		inline IFSM(std::string a_strStateName = "")
		{
			m_strStateName = a_strStateName;
		}
	};

	template<typename T_STATE, typename = typename std::enable_if<std::is_base_of<IFSM, T_STATE>::value>::type >
	class  FSM
	{
	protected:
		bool m_bIsTransitionToSelfAllowed = false;

		FSM(T_STATE* a_pStartState, bool a_bIsTransitionToSelfAllowed = false)
			: m_pCurrentState{ a_pStartState },
			m_bIsTransitionToSelfAllowed{ a_bIsTransitionToSelfAllowed }
		{
			m_pCurrentState->OnStateEnter();

			std::cout << "InitialState :: '" << m_pCurrentState->getStateName() << "'\n";
			RegisterState(a_pStartState);
		};

		FSM(std::vector<T_STATE*> a_pVectState, bool a_bIsTransitionToSelfAllowed = false)
			: m_pCurrentState{ a_pVectState[0] },
			m_bIsTransitionToSelfAllowed{ a_bIsTransitionToSelfAllowed }
		{
			m_pCurrentState->OnStateEnter();
				
			for (auto& l_State : a_pVectState)
			{
				RegisterState(l_State);
			}

			std::cout << "Total num of states: : '" << std::to_string(m_vectStates.size()) + "'\n";
		};

		virtual ~FSM() 
		{
			
		};

		std::vector<IFSM*> m_vectStates;

		IFSM* m_pCurrentState = nullptr;

		virtual void transitionTo(std::string a_strTransitionTo)
		{
			IFSM* l_pRegisteredState = getStateRegisteredWithID(a_strTransitionTo);
			if (l_pRegisteredState == nullptr)
			{
				std::cout << "FSM::RegisterState:: State with name '" << a_strTransitionTo << "' does not exist in the state list.\n";
				return;
			}

			if ((l_pRegisteredState == m_pCurrentState) && !m_bIsTransitionToSelfAllowed)
			{
				return;
			}

			m_pCurrentState->OnStateExit();
			m_pCurrentState = l_pRegisteredState;
			m_pCurrentState->OnStateEnter();
		}

		///Registers the state with name to the vect list of states if it does not already exist
		void RegisterState(T_STATE* a_pStateToRegister)
		{
			IFSM* l_pCurrentState = dynamic_cast<IFSM*>(a_pStateToRegister);

			if (l_pCurrentState == nullptr)
			{
				std::cout << "FSM::RegisterState:: State is not a derived class of IFSM.\n";
				return;
			}

			if (getStateRegisteredWithID(l_pCurrentState->getStateName()) != nullptr)
			{
				std::cout << "FSM::RegisterState:: State with name '" << l_pCurrentState->getStateName() << "' already exists in the list of states.\n";
				return;
			}

			m_vectStates.emplace_back(a_pStateToRegister);
		}

		///Checks if the state with given state name already exists in the vector of all states.
		IFSM* getStateRegisteredWithID(const std::string& a_strStateName)
		{
			size_t l_iStateCount = m_vectStates.size();

			for (size_t l_iStateIndex = 0; l_iStateIndex < l_iStateCount; l_iStateIndex++)
			{
				if (std::strcmp(a_strStateName.c_str(), m_vectStates[l_iStateIndex]->getStateName().c_str()) == 0)
				{
					return m_vectStates[l_iStateIndex];
				}
			}
			return nullptr;
		}
	};
}