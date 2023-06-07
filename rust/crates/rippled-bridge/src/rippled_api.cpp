//
// Created by Noah Kramer on 4/17/23.
//

#include "rippled-bridge/include/rippled_api.h"
#include "ripple/basics/base64.h"
#include "rippled-bridge/src/lib.rs.h"
#include <functional>
#include <string>
#include <iostream>

std::unique_ptr <std::string>
base64_decode_ptr(std::string const &data) {
    return std::make_unique<std::string>(ripple::base64_decode(data));
}

std::unique_ptr <ripple::NotTEC>
from_tefcodes(ripple::TEFcodes code) {
    return std::make_unique<ripple::NotTEC>(ripple::NotTEC(code));
}

std::unique_ptr <ripple::STTx> tx_ptr(ripple::PreflightContext const &ctx) {
    return std::make_unique<ripple::STTx>(ctx.tx);
}

// Test function to simulate the creation of an AccountID.
ripple::AccountID const &xrp_account() {
    return ripple::xrpAccount();
}

ripple::uint256 const &fixMasterKeyAsRegularKey() {
    return ripple::fixMasterKeyAsRegularKey;
}

ripple::XRPAmount defaultCalculateBaseFee(ripple::ReadView const& view, ripple::STTx const& tx) {
    return ripple::Transactor::calculateBaseFee(view, tx);
}

ripple::XRPAmount minimumFee(
        ripple::Application& app,
        ripple::XRPAmount baseFee,
        ripple::Fees const& fees,
        ripple::ApplyFlags flags
) {
    return ripple::Transactor::minimumFee(app, baseFee, fees, flags);
}

bool setFlag(
        std::shared_ptr<ripple::SLE>const & sle,
        std::uint32_t f) {
    return sle->setFlag(f);
}

void setAccountID(
        std::shared_ptr<ripple::SLE>const & sle,
        ripple::SField const& field,
        ripple::AccountID const& v
) {
    sle->setAccountID(field, v);
}

void setFieldAmountXRP(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    ripple::XRPAmount const& xrpAmount
) {
    sle->setFieldAmount(field, ripple::STAmount(xrpAmount));
}

void setPluginType(
        std::shared_ptr<ripple::SLE>const & sle,
        ripple::SField const& field,
        ripple::STPluginType const& v
) {
    sle->setPluginType(field, v);
}

void setFieldArray(
    std::shared_ptr<ripple::SLE>const& sle,
    ripple::SField const& field,
    std::unique_ptr<ripple::STArray> value
) {
    sle->setFieldArray(field, *value);
}

void setFieldU8(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    std::uint8_t v
) {
    sle->setFieldU8(field, v);
}

void setFieldU16(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    std::uint16_t v
) {
    sle->setFieldU16(field, v);
}

void setFieldU32(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    std::uint32_t v
) {
    sle->setFieldU32(field, v);
}

void setFieldU64(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    std::uint64_t v
) {
    sle->setFieldU64(field, v);
}

void setFieldH160(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    ripple::uint160 const& v
) {
    sle->setFieldH160(field, v);
}

void setFieldH256(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    ripple::uint256 const& v
) {
    sle->setFieldH256(field, v);
}

void setFieldBlob(
    std::shared_ptr<ripple::SLE>const & sle,
    ripple::SField const& field,
    ripple::STBlob const& v
) {
    sle->setFieldBlob(field, v);
}


void makeFieldAbsent(
        std::shared_ptr<ripple::SLE>const & sle,
ripple::SField const& field
) {
    sle->makeFieldAbsent(field);
}

std::unique_ptr<std::string> toBase58(const ripple::AccountID& accountId) {
    std::cout << "Size: " << sizeof(ripple::NotTEC) << " Alignement: " << alignof(ripple::NotTEC) << std::endl;
    return std::make_unique<std::string>(ripple::toBase58(accountId));
}

void push_soelement(int field_code, ripple::SOEStyle style, std::vector<ripple::FakeSOElement>& vec) {
    vec.push_back({field_code, style});
}

void push_stype_export(int tid, CreateNewSFieldPtr createNewSFieldPtr, ParseLeafTypeFnPtr parseLeafTypeFn, STypeFromSITFnPtr sTypeFromSitFnPtr, STypeFromSFieldFnPtr sTypeFromSFieldFnPtr, std::vector<STypeExport>& vec) {
    vec.push_back({tid, createNewSFieldPtr, parseLeafTypeFn, sTypeFromSitFnPtr, sTypeFromSFieldFnPtr});
}

void push_sfield_info(int tid, int fv, const char * txt_name, std::vector<ripple::SFieldInfo>& vec) {
    vec.push_back({tid, fv, txt_name});
}

ripple::SField const& constructSField(int tid, int fv, const char* fn) {
    if (ripple::SField const& field = ripple::SField::getField(ripple::field_code(tid, fv)); field != ripple::sfInvalid)
        return field;
    return *(new ripple::TypedField<ripple::STPluginType>(tid, fv, fn));
}

std::unique_ptr<OptionalSTVar> make_stvar(ripple::SField const& field, rust::Slice<const uint8_t> slice) {
//    ripple::Buffer buffer = ripple::Buffer(slice.data(), slice.size());
    std::unique_ptr<OptionalSTVar> ret = std::make_unique<OptionalSTVar>(ripple::detail::make_stvar<ripple::STPluginType>(field, ripple::Buffer(slice.data(), slice.size())));
    return ret;
}

void bad_type(Json::Value& error, std::string const& json_name, std::string const& field_name) {
    error = ripple::bad_type(json_name, field_name);
}

void invalid_data(Json::Value& error, std::string const& json_name, std::string const& field_name) {
    error = ripple::invalid_data(json_name, field_name);
}

std::unique_ptr<std::string> asString(Json::Value const& value) {
    return std::make_unique<std::string>(value.asString());
}

std::unique_ptr<ripple::Buffer> getVLBuffer(ripple::SerialIter& sit) {
    const ripple::Buffer &buffer = sit.getVLBuffer();
    return std::make_unique<ripple::Buffer>(buffer);
}

std::unique_ptr<ripple::STPluginType> make_stype(ripple::SField const& field, std::unique_ptr<ripple::Buffer> buffer) {
    return std::make_unique<ripple::STPluginType>(ripple::STPluginType(field, ripple::Buffer(buffer.get()->data(), buffer.get()->size())));
}

std::unique_ptr<ripple::STBase> make_empty_stype(ripple::SField const& field) {
    return std::make_unique<ripple::STBase>(ripple::STPluginType(field));
}

ripple::SField const& getSField(int type_id, int field_id) {
    return ripple::SField::getField(ripple::field_code(type_id, field_id));
}

std::shared_ptr<ripple::SLE> new_sle(ripple::Keylet const& k) {
    return std::make_shared<ripple::SLE>(k);
}

std::unique_ptr<std::optional<std::uint64_t>>
dir_insert(ripple::ApplyView& view, ripple::Keylet const& directory, ripple::Keylet const& key, ripple::AccountID const& account) {
    std::optional<std::uint64_t> result =
        view.dirInsert(directory, key, ripple::describeOwnerDir(account));
    return std::make_unique<std::optional<std::uint64_t>>(result);
}

bool has_value(const std::unique_ptr<std::optional<std::uint64_t>> & optional) {
    return optional->has_value();
}

std::uint64_t get_value(const std::unique_ptr<std::optional<std::uint64_t>> & optional) {
    return optional->value();
}

bool opt_uint256_has_value(const std::unique_ptr<std::optional<ripple::uint256>> & optional) {
    return optional->has_value();
}
ripple::uint256 opt_uint256_get_value(const std::unique_ptr<std::optional<ripple::uint256>> & optional) {
    return optional->value();
}

std::unique_ptr<OptionalUint256> apply_view_succ(ripple::ApplyView& applyView, ripple::Keylet const& key, ripple::Keylet const& last) {
    std::optional<ripple::uint256> result =
        applyView.succ(key.key, last.key);
    return std::make_unique<std::optional<ripple::uint256>>(result);
}

std::unique_ptr<OptionalUint256> read_view_succ(ripple::ReadView const& readView, ripple::Keylet const& key, ripple::Keylet const& last) {
    std::optional<ripple::uint256> result =
        readView.succ(key.key, last.key);
    return std::make_unique<std::optional<ripple::uint256>>(result);
}

void
adjustOwnerCount(
    ripple::ApplyView& view,
    std::shared_ptr<ripple::SLE> const& sle,
    std::int32_t amount,
    beast::Journal const& j)
{
//    beast::Journal actual = *j;
//    beast::Journal *journal = &j;
    ripple::adjustOwnerCount(view, sle, amount, j);
}

ripple::STBlob const& new_st_blob(ripple::SField const& field, std::uint8_t const* data, std::size_t size) {
    return *(new ripple::STBlob(field, data, size));
}

ripple::STObject const& get_from_const_st_array(ripple::STArray const& array, std::size_t index) {
    return array[index];
}

std::unique_ptr<ripple::STObject> get_from_st_array(ripple::STArray const& array, std::size_t index) {
    return std::make_unique<ripple::STObject>(array[index]);
}

std::unique_ptr<ripple::STObject> create_inner_object(ripple::SField const& field) {
    ripple::SOTemplate const* objectTemplate =
        ripple::InnerObjectFormats::getInstance().findSOTemplateBySField(field);

    return std::make_unique<ripple::STObject>(*objectTemplate, field);
}

std::unique_ptr<ripple::STArray> peekFieldArray(std::shared_ptr<ripple::STObject> obj, ripple::SField const& field) {
    return std::make_unique<ripple::STArray>(obj->peekFieldArray(field));
}

