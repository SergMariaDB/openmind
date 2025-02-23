//
// Created by Сергей Кривонос on 01.09.17.
//
#pragma once
#include <omnn/math/Variable.h>
#include <omnn/math/DuoValDescendant.h>

namespace omnn::math {

class Exponentiation
        : public DuoValDescendant<Exponentiation>
{
	using base = DuoValDescendant<Exponentiation>;
    vars_cont_t v;
    void InitVars();

protected:
    Valuable& ebase() { return base::_1; }
    Valuable& eexp() { return base::_2; }
    std::ostream& print_sign(std::ostream& out) const override;
public:
    std::ostream& code(std::ostream& out) const override;

    // DONT: overrides behaviour (calls InitVars)
	// using base::base;

	template <class BaseT, class ExponentiationT>
    Exponentiation(BaseT&& b, ExponentiationT&& e)
        : base(std::forward<BaseT>(b), std::forward<ExponentiationT>(e))
	{
        InitVars();
    }

    bool IsExponentiation() const override { return true; }
    bool IsVaExp() const override { return ebase().IsVa(); }
    bool IsSimple() const override {
		return !FindVa() && eexp().IsInt();
	}


    YesNoMaybe IsMultival() const override;
    void Values(const std::function<bool(const Valuable&)>&) const override;
    const Valuable& getBase() const { return _1; }
    const Valuable& ebase() const { return _1; }
    template<class T>
    void setBase(T&& b)
    {
		set1(::std::forward<T>(b));
        InitVars();
        optimized = {};
	}
    template<class T>
    void updateBase(T&& b)
    {
		update1(std::forward<T>(b));
        InitVars();
        optimized = {};
	}

    const Valuable& eexp() const { return _2; }
    const Valuable& getExponentiation() const { return _2; }
    template<class T>
    void setExponentiation(T&& exponentiation)
    {
		set1(std::forward<T>(exponentiation));
        InitVars();
        optimized = {};
	}
    template<class T>
    void updateExponentiation(T&& exponentiation)
    {
		update2(std::forward<T>(exponentiation));
        InitVars();
        optimized = {};
    }
    
    static max_exp_t getMaxVaExp(const Valuable& b, const Valuable& e);
    max_exp_t getMaxVaExp() const override;

    // virtual operators
    Valuable& operator +=(const Valuable& v) override;
    Valuable& operator *=(const Valuable& v) override;
    bool MultiplyIfSimplifiable(const Valuable& v) override;
    std::pair<bool,Valuable> IsMultiplicationSimplifiable(const Valuable& v) const override;
    bool SumIfSimplifiable(const Valuable& v) override;
    std::pair<bool,Valuable> IsSummationSimplifiable(const Valuable& v) const override;
    Valuable& operator /=(const Valuable& v) override;
    Valuable& operator ^=(const Valuable&) override;
    bool operator ==(const Valuable&) const override;
    explicit operator double() const override;
    Valuable& d(const Variable& x) override;
    void integral(const Variable& x, const Variable& C) override;
    
    bool operator <(const Valuable& v) const override;
    void optimize() override;
    
    Valuable varless() const override;
    const vars_cont_t& getCommonVars() const override;
    Valuable InCommonWith(const Valuable& v) const override;
    bool IsComesBefore(const Valuable& v) const override;
    Valuable calcFreeMember() const override;

    Valuable& sq() override;
    Valuable Sqrt() const override;
    Valuable& sqrt() override;

    Valuable operator()(const Variable&) const override;
    Valuable operator()(const Variable& v, const Valuable& augmentation) const override;

    solutions_t Distinct() const override;

    bool IsNormalizedPolynomial(const Variable&) const override;
    void solve(const Variable& va, solutions_t&) const override;
};

}
