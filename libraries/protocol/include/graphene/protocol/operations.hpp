/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <graphene/protocol/base.hpp>
#include <graphene/protocol/account.hpp>
#include <graphene/protocol/assert.hpp>
#include <graphene/protocol/asset_ops.hpp>
#include <graphene/protocol/balance.hpp>
#include <graphene/protocol/custom.hpp>
#include <graphene/protocol/committee_member.hpp>
#include <graphene/protocol/confidential.hpp>
#include <graphene/protocol/custom_authority.hpp>
#include <graphene/protocol/fba.hpp>
#include <graphene/protocol/proposal.hpp>
#include <graphene/protocol/ticket.hpp>
#include <graphene/protocol/transfer.hpp>
#include <graphene/protocol/vesting.hpp>
#include <graphene/protocol/withdraw_permission.hpp>
#include <graphene/protocol/witness.hpp>
#include <graphene/protocol/worker.hpp>
#include <graphene/protocol/personal_data.hpp>
#include <graphene/protocol/content_card.hpp>
#include <graphene/protocol/permission.hpp>
#include <graphene/protocol/content_vote.hpp>
#include <graphene/protocol/commit_reveal.hpp>

namespace graphene { namespace protocol {

   /**
    * @ingroup operations
    *
    * Defines the set of valid operations as a discriminated union type.
    */
   typedef fc::static_variant<
            transfer_operation,
            account_create_operation,
            account_update_operation,
            account_whitelist_operation,
            account_upgrade_operation,
            account_transfer_operation,
            asset_create_operation,
            asset_update_operation,
            asset_update_bitasset_operation,
            asset_update_feed_producers_operation,
            asset_issue_operation,
            asset_reserve_operation,
            asset_fund_fee_pool_operation,
            asset_settle_operation,
            asset_global_settle_operation,
            asset_publish_feed_operation,
            witness_create_operation,
            witness_update_operation,
            proposal_create_operation,
            proposal_update_operation,
            proposal_delete_operation,
            withdraw_permission_create_operation,
            withdraw_permission_update_operation,
            withdraw_permission_claim_operation,
            withdraw_permission_delete_operation,
            committee_member_create_operation,
            committee_member_update_operation,
            committee_member_update_global_parameters_operation,
            vesting_balance_create_operation,
            vesting_balance_withdraw_operation,
            custom_operation,
            assert_operation,
            balance_claim_operation,        // VIRTUAL
            override_transfer_operation,
            transfer_to_blind_operation,
            blind_transfer_operation,
            transfer_from_blind_operation,
            asset_settle_cancel_operation,  // VIRTUAL
            asset_claim_fees_operation,
            fba_distribute_operation,       // VIRTUAL
            asset_claim_pool_operation,
            asset_update_issuer_operation,
            custom_authority_create_operation,
            custom_authority_update_operation,
            custom_authority_delete_operation,
            ticket_create_operation,
            ticket_update_operation,
            personal_data_create_operation,
            personal_data_remove_operation,
            content_card_create_operation,
            content_card_update_operation,
            content_card_remove_operation,
            permission_create_operation,
            permission_remove_operation,
            content_vote_create_operation,
            content_vote_remove_operation,
            vote_counter_update_operation,
            commit_create_operation,        // VIRTUAL
            reveal_create_operation         // VIRTUAL
         > operation;

   /// @} // operations group

   /**
    *  Appends required authorites to the result vector.  The authorities appended are not the
    *  same as those returned by get_required_auth 
    *
    *  @return a set of required authorities for @ref op
    */
   void operation_get_required_authorities( const operation& op,
                                            flat_set<account_id_type>& active,
                                            flat_set<account_id_type>& owner,
                                            vector<authority>& other,
                                            bool ignore_custom_operation_required_auths );

   void operation_validate( const operation& op );

   /**
    *  @brief necessary to support nested operations inside the proposal_create_operation
    */
   struct op_wrapper
   {
      public:
         op_wrapper(const operation& op = operation()):op(op){}
         operation op;
   };

} } // graphene::protocol

FC_REFLECT_TYPENAME( graphene::protocol::operation )
FC_REFLECT( graphene::protocol::op_wrapper, (op) )

GRAPHENE_DECLARE_EXTERNAL_SERIALIZATION( graphene::protocol::op_wrapper )
