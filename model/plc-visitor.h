/*
 * plc-visitor.h
 *
 *  Created on: 2012-01-06
 *      Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#ifndef PLC_VISITOR_H_
#define PLC_VISITOR_H_


#include "plc-defs.h"
#include "plc-time.h"
#include "plc-outlet.h"
#include "plc-backbone.h"

namespace ns3 {

/**
 *	Visitor implementation for boost depth first search
 *	to discover outlets seen from the bridge tap of the backbone
 *	branch
 */
class PLC_OutletDiscoverVisitor : public boost::default_dfs_visitor
{
public:
	PLC_OutletDiscoverVisitor(PLC_BackboneBranch *bb_branch) : m_bb_branch(bb_branch) {}

	~PLC_OutletDiscoverVisitor() {}

	template < typename Vertex, typename Graph >
	void finish_vertex(Vertex u, const Graph & g)
	{
		this->m_bb_branch->GetNodePeekPtr()->GetGraph()->Lock();
		PLC_Node *node = this->m_bb_branch->GetNodePeekPtr()->GetGraph()->GetNodePeekPtr(u);
		this->m_bb_branch->GetNodePeekPtr()->GetGraph()->Unlock();

		node->Lock();
		if (node->HasOutlet()) {

			// register outlet on backbone branch
			PLC_Outlet *outlet = node->GetOutletPeekPtr();
			outlet->RegisterBackboneBranch(this->m_bb_branch);

			if (node->IsTimeVariant())
			{
				this->m_bb_branch->SetTimeVariant();
			}
		}
		node->Unlock();
	}

private:
	PLC_BackboneBranch *m_bb_branch;
};

}

#endif /* PLC_VISITOR_H_ */
