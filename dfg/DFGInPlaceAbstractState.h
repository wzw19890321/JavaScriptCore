/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef DFGInPlaceAbstractState_h
#define DFGInPlaceAbstractState_h

#if ENABLE(DFG_JIT)

#include "DFGAbstractValue.h"
#include "DFGBranchDirection.h"
#include "DFGGraph.h"
#include "DFGMergeMode.h"
#include "DFGNode.h"

namespace JSC { namespace DFG {

class InPlaceAbstractState {
public:
    InPlaceAbstractState(Graph&);
    
    ~InPlaceAbstractState();
    
    void createValueForNode(Node*) { }
    
    AbstractValue& forNode(Node* node)
    {
        return node->value;
    }
    
    AbstractValue& forNode(Edge edge)
    {
        return forNode(edge.node());
    }
    
    Operands<AbstractValue>& variables()
    {
        return m_variables;
    }
    
    // Call this before beginning CFA to initialize the abstract values of
    // arguments, and to indicate which blocks should be listed for CFA
    // execution.
    void initialize();

    // Start abstractly executing the given basic block. Initializes the
    // notion of abstract state to what we believe it to be at the head
    // of the basic block, according to the basic block's data structures.
    // This method also sets cfaShouldRevisit to false.
    void beginBasicBlock(BasicBlock*);
    
    BasicBlock* block() const { return m_block; }
    
    // Finish abstractly executing a basic block. If MergeToTail or
    // MergeToSuccessors is passed, then this merges everything we have
    // learned about how the state changes during this block's execution into
    // the block's data structures. There are three return modes, depending
    // on the value of mergeMode:
    //
    // DontMerge:
    //    Always returns false.
    //
    // MergeToTail:
    //    Returns true if the state of the block at the tail was changed.
    //    This means that you must call mergeToSuccessors(), and if that
    //    returns true, then you must revisit (at least) the successor
    //    blocks. False will always be returned if the block is terminal
    //    (i.e. ends in Throw or Return, or has a ForceOSRExit inside it).
    //
    // MergeToSuccessors:
    //    Returns true if the state of the block at the tail was changed,
    //    and, if the state at the heads of successors was changed.
    //    A true return means that you must revisit (at least) the successor
    //    blocks. This also sets cfaShouldRevisit to true for basic blocks
    //    that must be visited next.
    bool endBasicBlock(MergeMode);
    
    // Reset the AbstractState. This throws away any results, and at this point
    // you can safely call beginBasicBlock() on any basic block.
    void reset();
    
    // Did the last executed node clobber the world?
    bool didClobber() const { return m_didClobber; }
    
    // Is the execution state still valid? This will be false if execute() has
    // returned false previously.
    bool isValid() const { return m_isValid; }
    
    // Merge the abstract state stored at the first block's tail into the second
    // block's head. Returns true if the second block's state changed. If so,
    // that block must be abstractly interpreted again. This also sets
    // to->cfaShouldRevisit to true, if it returns true, or if to has not been
    // visited yet.
    bool merge(BasicBlock* from, BasicBlock* to);
    
    // Merge the abstract state stored at the block's tail into all of its
    // successors. Returns true if any of the successors' states changed. Note
    // that this is automatically called in endBasicBlock() if MergeMode is
    // MergeToSuccessors.
    bool mergeToSuccessors(BasicBlock*);
    
    // Methods intended to be called from AbstractInterpreter.
    void setDidClobber(bool didClobber) { m_didClobber = didClobber; }
    void setIsValid(bool isValid) { m_isValid = isValid; }
    void setBranchDirection(BranchDirection branchDirection) { m_branchDirection = branchDirection; }
    void setFoundConstants(bool foundConstants) { m_foundConstants = foundConstants; }
    bool haveStructures() const { return m_haveStructures; } // It's always safe to return true.
    void setHaveStructures(bool haveStructures) { m_haveStructures = haveStructures; }

private:
    bool mergeStateAtTail(AbstractValue& destination, AbstractValue& inVariable, Node*);

    static bool mergeVariableBetweenBlocks(AbstractValue& destination, AbstractValue& source, Node* destinationNode, Node* sourceNode);
    
    Graph& m_graph;
    
    Operands<AbstractValue> m_variables;
    BasicBlock* m_block;
    
    bool m_haveStructures;
    bool m_foundConstants;
    
    bool m_isValid;
    bool m_didClobber;
    
    BranchDirection m_branchDirection; // This is only set for blocks that end in Branch and that execute to completion (i.e. m_isValid == true).
};

} } // namespace JSC::DFG

#endif // ENABLE(DFG_JIT)

#endif // DFGInPlaceAbstractState_h

