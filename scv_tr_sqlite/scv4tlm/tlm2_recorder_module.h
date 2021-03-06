/*
 * tlm_recorder.h
 *
 *  Created on: 07.11.2015
 *      Author: eyck
 */

#ifndef TLM2_RECORDER_MODULE_H_
#define TLM2_RECORDER_MODULE_H_

#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "tlm2_recorder.h"

namespace scv4tlm {
/*! \brief The TLM2 transaction recorder
 *
 * This module records all TLM transaction to a SCV transaction stream for further viewing and analysis.
 * The handle of the created transaction is storee in an tlm_extension so that another instance of the scv_tlm2_recorder
 * e.g. further down the opath can link to it.
 * The transaction recorder is simply bound between an existing pair of initiator and target sockets
 */
template<unsigned int BUSWIDTH = 32, typename TYPES=tlm::tlm_base_protocol_types>
class tlm2_recorder_module: public sc_core::sc_module, public tlm2_recorder<TYPES> {
public:
	SC_HAS_PROCESS(tlm2_recorder_module);
	//! The target socket of the recorder to be bound to the initiator
	tlm::tlm_target_socket<BUSWIDTH, TYPES, 1> target;
	//! The initiator to be bound to the target socket
	tlm::tlm_initiator_socket<BUSWIDTH, TYPES, 1> initiator;


	/*! \brief The constructor of the component
	 *
	 * \param name is the SystemC module name of the recorder
	 * \param tr_db is a pointer to a transaction recording database. If none is provided the default one is retrieved.
	 *        If this database is not initialized (e.g. by not calling scv_tr_db::set_default_db() ) recording is disabled.
	 */
	tlm2_recorder_module(sc_core::sc_module_name name, bool recording_enabled = true, scv_tr_db* tr_db = scv_tr_db::get_default_db())
	: sc_module(name)
	, tlm2_recorder<TYPES>(recording_enabled, tr_db)
	{
		// bind the sockets to the module
		target.bind(*this);
		initiator.bind(*this);
	}

	virtual ~tlm2_recorder_module(){}

	virtual tlm::tlm_fw_transport_if<tlm::tlm_base_protocol_types>* get_fw_if() {
		return initiator.get_base_port().operator->();
	}
	virtual tlm::tlm_bw_transport_if<tlm::tlm_base_protocol_types>* get_bw_if() {
		return target.get_base_port().operator->();
	}

};
} // namespace


#endif /* TLM2_RECORDER_MODULE_H_ */
