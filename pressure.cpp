#include "pressure.h"

class pressure:public std::exception{
    virtual const char* what() const throw(){
        return "Systolic / Diastolic pressure not found.";
    }
}pressureException;

class NullValue : public std::exception{
    virtual const char* what() const throw(){
        return "NULL Pointer";
    }
}nullValue;

	// Contructor.
	Pressure::Pressure() {

		bloodPressure.clear();
		systolic = -1;
		diastolic = -1;
		m_position = NULL;
	}

	// Read the data.

	void Pressure::LerDados(int* position, int size) {

		try {
			if(position == NULL)
				throw nullValue;
		}
		catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }

		m_size = size;

		m_position = position;
	}

/*
	// Read the data.
	void Pressure::LerDados(int* position, int size) {

		std::ifstream arquivo;

        arquivo.open("test.txt");

        int valor;

        while(!arquivo.eof()) {

            arquivo >> valor;
            bloodPressure.push_back(valor);
        }

        arquivo.close();

		m_size = bloodPressure.size();

		m_position = (int*)malloc(m_size);

		m_position = &bloodPressure[0];

	}*/


	// Find the systolic / diastolic pressure.
	void Pressure::Pressures(int* position, int size, int index) {

		LerDados(position, size);

        FindLocalMaxMin();

        int systolicValueLeft, systolicValueRigth;
        int diastolicValueLeft, diastolicValueRigth;

        try {

            systolicValueRigth = SystolicPressure(index - 1, 0);
            diastolicValueLeft = DiastolicPresure(index - 1, 0);

            systolicValueLeft = SystolicPressure(index - 1, 1);
            diastolicValueRigth = DiastolicPresure(index - 1, 1);

            systolic = RealValueSystolic(index, systolicValueLeft, systolicValueRigth);
            diastolic = RealValueDiastolic(index,diastolicValueLeft, diastolicValueRigth);

            if(systolic == -1 || diastolic == -1)
                throw pressureException;

        }
        catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
	}

	// Return systolic pressure.
	int Pressure::GetSystolic() {
		return systolic;
	}

	// Return diastolic pressure.
	int Pressure::GetDiastolic() {
		return diastolic;
	}

	// Find max and notch.
	void Pressure::FindLocalMaxMin() {

	    MaxLocal();
	    MinLocal();
	}

	// Destructor
	Pressure::~Pressure() {
		m_position = NULL;
		free(m_position);
		delete m_position;
	}

	void Pressure::MaxLocal() {

	    for(int i = 1; i < m_size-1; i++) {

	        if(m_position[i] == m_position[i - 1] && m_position[i] > m_position[i + 1]) {

	            int j = i - 1;

				while(m_position[i] == m_position[j] && j > 0) {
	                j--;
	            }

	            if(m_position[i] > m_position[j]) {

	                if(m_position[i] > m_position[i + 1]) {
	                    localMax.push_back(i);
	                }
	            }
	        }

	        if(m_position[i] > m_position[i - 1]) {

	            if(m_position[i] > m_position[i + 1]) {
	                localMax.push_back(i);
	            }
	        }
	    }
	}

	void Pressure::MinLocal()
	{

	    for(int i = 1; i < m_size-1; i++) {

	        if(m_position[i] == m_position[i - 1] && m_position[i] < m_position[i + 1]) {

	            int j = i - 1;

				while(m_position[i] == m_position[j] && j > 0) {
	                j--;
	            }

	            if(m_position[i] < m_position[j] || j == 0) {

	                if(m_position[i] < m_position[i + 1]) {
	                    localMin.push_back(i);
	                }
	            }
	        }

	        if(m_position[i] < m_position[i - 1]) {

	            if(m_position[i] < m_position[i + 1]) {
	                localMin.push_back(i);
	            }
	        }
	    }
	}

	// Find systolic pressure.
	int Pressure::SystolicPressure(int index, int nLado) {

		if((index + 1) > m_size || (index - 1) < 0)
			return -1;

        if(nLado == 0) {

            if(find(localMax.begin(), localMax.end(), index) !=  localMax.end()) {

                if(!IsPositiveFalse(index))
                    return index + 1;
            }

            return SystolicPressure(index + 1, nLado);
        }
        else {

            if(find(localMax.begin(), localMax.end(), index) !=  localMax.end()) {

                if(!IsPositiveFalse(index))
                    return index + 1;
            }

            return SystolicPressure(index - 1, nLado);
        }
	}


	// Find diastolic pressure.
	int Pressure::DiastolicPresure(int index, int nLado) {

		if((index - 1) < 0 || ((index + 1) > m_size))
			return -1;

        if(nLado == 0) {

            if(find(localMin.begin(), localMin.end(), index) !=  localMin.end()) {

                if(!IsPositiveFalseDiastolicPresure(index))
                    return index + 1;
            }

            return DiastolicPresure(index + 1, nLado);
        }
        else {

            if(find(localMin.begin(), localMin.end(), index) !=  localMin.end()) {

                if(!IsPositiveFalseDiastolicPresure(index))
                    return index + 1;
            }

            return DiastolicPresure(index - 1, nLado);
        }
	}

	bool Pressure::IsPositiveFalse(int nIndex) {

        if(nIndex <= 0)
            return false;

        std::vector<int>::iterator pos = find(localMax.begin(), localMax.end(), nIndex);

        if( pos !=  localMax.end()) {

            int indexAtualLocal = distance(localMax.begin(), pos);
            int nextIndexLocal = indexAtualLocal+1;

            int index = localMax[indexAtualLocal];
            int nextIndex = localMax[nextIndexLocal];

            if(index < 0 || index == m_size)
                return false;

            if(m_position[index] > m_position[nextIndex])
                return false;
            else
                return true;
        }
        else
            return true;
	}

    bool Pressure::IsPositiveFalseDiastolicPresure(int nIndex) {

        if(nIndex == 0)
            return false;

        std::vector<int>::iterator pos = find(localMin.begin(), localMin.end(), nIndex);

        if( pos !=  localMin.end()) {

            int indexAtualLocal = distance(localMin.begin(), pos);
            int nextIndexLocal = indexAtualLocal+1;

            int index = localMin[indexAtualLocal];
            int nextIndex = localMin[nextIndexLocal];

            if(index < 0 || index == m_size)
                return false;

            if(m_position[index] < m_position[nextIndex])
                return false;
            else
                return true;
        }
        else
            return true;
	}

	int Pressure::RealValueSystolic(int index, int systolicLeft, int systolicRight)
	{
        if(std::min(systolicRight, systolicLeft) == -1){
            return (std::max(systolicRight, systolicLeft));
        }else{
            if((systolicRight - index) > (index  - systolicLeft))
                return systolicLeft;
            else
                return systolicRight;

        }
	}

	int Pressure::RealValueDiastolic(int index, int diastolicLeft, int diastolicRight)
	{
        if(std::min(diastolicRight, diastolicLeft) == -1)
        {
            return (std::max(diastolicRight, diastolicLeft));
        }
        else{
            if(diastolicRight > index)
                return(diastolicLeft);
            else
                if(abs(index - diastolicRight) <= abs(index - diastolicLeft))
                    return (diastolicRight);
        }
	}

