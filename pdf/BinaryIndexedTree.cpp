template <typename T>
class BinaryIndexedTree{
	public:
		void init(int _n, T _zero)
		{
			n = _n; zero = _zero;
			bit_array.clear();
			bit_array.resize(n+1,zero);
		}
		/*void init(int n)
		{
			total_size = n+1;
			bit.clear(); bit_array.resize(n+1);
			memset(&bit_array[0],0,sizeof(T) * total_size);
		}*/
		void init (const std::vector<T> &vect, T _zero)
		{
			n = vect.size(); zero = _zero;
			bit_array.clear(); bit_array.resize(n+1,zero);
			for(int i=0; i<n;i++) update(i,vect[i]);
		}

		T get_sum(int end)
		{
			end++;
			T sum = zero;
			while(end > 0){
				sum = sum + bit_array[end];
				end -= (end & (-end));
			}
			return sum;

		}

		void update(int index, T change)
		{
			index++;
			while(index <= n){
				bit_array[index] = bit_array[index] + change;
				index += (index & (-index));
			}
		}

	private:
		vector<T>	bit_array;
		T zero;
		int n;
};
