# include <iostream>
# include <algorithm>
# include <vector>
# include <string>
# include <functional>

namespace s3d
{
	using String = std::wstring;

	template <class Type>
	class Array : public std::vector<Type>
	{
	public:

		using std::vector<Type>::vector;

		Array& each(std::function<void(Type&)> f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		const Array& each(std::function<void(const Type&)> f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		Array& each_index(std::function<void(size_t, Type&)> f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		const Array& each_index(std::function<void(size_t, const Type&)> f) const
		{
			size_t i = 0;

			for (const auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		Array& map(std::function<Type(const Type&)> f)
		{
			for (auto& v : *this)
			{
				v = f(v);
			}

			return *this;
		}

		template <class Fty>
		auto mapped(Fty f) const
		{
			Array<decltype(std::declval<Fty>()(std::declval<Type>()))> new_array;

			new_array.reserve(std::vector<Type>::size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		String join(const String& sep) const
		{
			String s;

			bool isFirst = true;

			for (const auto& v : *this)
			{
				if (!std::exchange(isFirst, false))
				{
					s.append(sep);
				}

				s.append(std::to_wstring(v));
			}

			return s;
		}

		Array filtered(std::function<bool(const Type&)> f) const
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array& reverse()
		{
			std::reverse(std::vector<Type>::begin(), std::vector<Type>::end());

			return *this;
		}

		Array reversed() const
		{
			return Array(std::vector<Type>::rbegin(), std::vector<Type>::rend());
		}
	};

	template <class Type>
	Array<Type> Iota(Type end)
	{
		static_assert(std::is_integral<Type>::value, "Type should be of integral type");

		Array<Type> new_array;

		if (end <= 0)
		{
			return new_array;
		}

		new_array.reserve(end);

		for (Type x = 0; x < end; ++x)
		{
			new_array.push_back(x);
		}

		return new_array;
	}

	template <class Type>
	Array<Type> Iota(Type begin, Type end)
	{
		static_assert(std::is_integral<Type>::value, "Type should be of integral type");

		Array<Type> new_array;

		if (end <= begin)
		{
			return new_array;
		}

		new_array.reserve(end - begin);

		for (auto x = begin; x < end; ++x)
		{
			new_array.push_back(x);
		}

		return new_array;
	}
}

using namespace s3d;

int main()
{
	const Array<int> v = { 1,2,3,4,5 };

	std::wcout << L"----------------\n";
	std::wcout << v.join(L", ") << L'\n';

	std::wcout << L"----------------\n";
	v.mapped([](auto n) { return n * 0.5; })
	 .each([](const auto& x) { std::wcout << x << L'\n'; });

	std::wcout << L"----------------\n";
	v.each_index([](size_t idx, const auto& x) { std::wcout << idx * 100 + x << L'\n'; });

	std::wcout << L"----------------\n";
	std::wcout << v.filtered([](int n) { return n % 2 == 0; }).join(L", ") << L'\n';

	std::wcout << L"----------------\n";
	std::wcout << v.reversed().join(L", ") << L'\n';

	std::wcout << L"----------------\n";
	std::wcout << Iota(8).join(L", ") << L'\n';

	std::wcout << L"----------------\n";
	std::wcout << Iota(4, 8).join(L", ") << L'\n';
}
