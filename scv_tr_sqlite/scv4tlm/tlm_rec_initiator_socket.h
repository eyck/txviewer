/*
 * tlm_rec_target_socket.h
 *
 *  Created on: 08.11.2015
 *      Author: eyck
 */

#ifndef TLM_REC_INITIATOR_SOCKET_H_
#define TLM_REC_INITIATOR_SOCKET_H_

#include <tlm_core/tlm_2/tlm_sockets/tlm_initiator_socket.h>

#include "tlm2_recorder.h"

namespace scv4tlm {
template<unsigned int BUSWIDTH = 32, typename TYPES = tlm::tlm_base_protocol_types, int N = 1
#if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
		, sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
		>
class tlm_rec_initiator_socket: public tlm::tlm_initiator_socket<BUSWIDTH
, TYPES
, N
#if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
, POL
#endif
> {
	static std::string gen_name(const char* first, const char* second){
		std::stringstream ss;
		ss<<first<<"_"<<second;
		return ss.str();
	}
public:
	typedef tlm::tlm_fw_transport_if<TYPES>  fw_interface_type;
	typedef tlm::tlm_bw_transport_if<TYPES>  bw_interface_type;
	typedef sc_core::sc_port<fw_interface_type, N
#if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
			, POL
#endif
			>   port_type;
	typedef sc_core::sc_export<bw_interface_type> export_type;
	typedef tlm::tlm_base_target_socket_b<BUSWIDTH,
			fw_interface_type,
			bw_interface_type> base_target_socket_type;
	typedef tlm::tlm_base_initiator_socket_b<BUSWIDTH,
			fw_interface_type,
			bw_interface_type> base_type;

	tlm_rec_initiator_socket() :
		tlm::tlm_initiator_socket<BUSWIDTH
		, TYPES
		, N
#if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
, POL
#endif
>()
,recorder()
{
}

	explicit tlm_rec_initiator_socket(const char* name) :
						tlm::tlm_initiator_socket<BUSWIDTH
						, TYPES
						, N
#if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
						, POL
#endif
						>(name)
						,recorder(gen_name(name, "rec").c_str())
						{
						}

	virtual ~tlm_rec_initiator_socket(){}

	virtual const char* kind() const {
		return "tlm_rec_target_socket";
	}
	//
	// Bind initiator socket to target socket
	// - Binds the port of the initiator socket to the export of the target
	//   socket
	// - Binds the port of the target socket to the export of the initiator
	//   socket
	//
	virtual void bind(base_target_socket_type& s) {
		// initiator.port -> target.export
		(this->get_base_port())(recorder);
		recorder.fw_port(s.get_base_interface());
		// target.port -> initiator.export
		(s.get_base_port())(recorder);
		recorder.bw_port(this->get_base_interface());
	}
	//
	// Bind initiator socket to initiator socket (hierarchical bind)
	// - Binds both the export and the port
	//
	virtual void bind(base_type& s){
		// port
		(this->get_base_port())(recorder);
		recorder.fw_port(s.get_base_port());
		// export
		(s.get_base_export())(recorder);
		recorder.bw_port(this->get_base_export());
	}

	//
	// Bind interface to socket
	// - Binds the interface to the export of this socket
	//
	virtual void bind(bw_interface_type& ifs) {
		(this->get_base_export())(ifs);
	}

	void setExtensionRecording(tlm_extensions_recording_if<TYPES>* extensionRecording){
		recorder.setExtensionRecording(extensionRecording);
	}

protected:
	scv4tlm::tlm2_recorder<TYPES> recorder;
};

}
// namespace scv4tlm

#endif /* TLM_REC_TARGET_SOCKET_H_ */
