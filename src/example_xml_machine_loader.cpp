//============================================================================
// Name        : example_xml_machine_loader.cpp
// Author      : Cogniteam
// Version     :
// Copyright   : MIT
// Description :
//============================================================================

#include <cognitao/CogniTao.h>


int main(int argc, char* argv[]) {

	try
	{
		// init WM interface
		WM::init(new MapThreadSafeDataSource());

		if (argc < 2) {
            
			cout<<"-- MISSING XML FILE --"<<endl;
			return 1;

		} else {

			cout<< "Loading XML " << argv[1] << endl;
			Machine* m =  MachineXMLReader::read(argv[1]);
			MachineWebServer w("0.0.0.0", "1234", m);
			
			m->start();

			while (!m->isFinished())
			{
				// Print WM
            	cout<<WM::toString();    
            	// Print Execution State
            	cout<<MachineStringWriter::executionTrace(m->getExecutionState()) <<endl;
				
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			m->stop();
			delete m;
		}
	}
	catch (std::exception const& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 1;
}