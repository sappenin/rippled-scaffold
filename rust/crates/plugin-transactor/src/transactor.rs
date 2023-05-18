use std::pin::Pin;
use xrpl_rust_sdk_core::core::types::XrpAmount;
use rippled_bridge::{NotTEC, SOEStyle, TER};
use crate::{ApplyContext, PreclaimContext, PreflightContext, ReadView, STTx};

pub trait Transactor {
    fn pre_flight(ctx: PreflightContext) -> NotTEC;
    fn pre_claim(ctx: PreclaimContext) -> TER;
    fn calculate_base_fee(view: ReadView, tx: STTx) -> XrpAmount {
        rippled_bridge::rippled::defaultCalculateBaseFee(view.instance(), tx.instance).into()
    }
    fn do_apply<'a>(ctx: &'a mut ApplyContext<'a>, m_prior_balance: XrpAmount, m_source_balance: XrpAmount) -> TER;
    fn tx_format() -> Vec<SOElement>;
}

pub struct SOElement {
    pub field_code: i32,
    pub style: SOEStyle
}