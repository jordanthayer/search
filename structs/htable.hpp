#include <vector>
#include <boost/optional.hpp>

template <class Key, class Val> class Htable {
public:

	Htable(unsigned int sz = 256) : fill(0) {
		bkts.reserve(sz);
	}

	void add(Key k, Val v) {
		if (fill * 3 >= bkts.size())
			grow();

		unsigned int ind = k.hash() % bkts.size();
		bkts[ind].push_back(pair(k, v));
		fill++;
	}

	boost::optional<Val>  repl(Key k, Val v) {
		unsigned int ind = k.hash() % bkts.size();

		for (int i = 0; i < bkts[ind].size(); i++) {
			std::pair<Key, Val> &e = bkts[ind][i];
			if (k == e.first) {
				Val old = e.second;
				e.second = e.v;
				return boost::optional<Val>(old);
			}
		}

		bkts[ind].push_back(pair(k, v));
		fill++;

		return boost::optional<Val>();
	}

	bool mem(Key k) {
		unsigned int ind = k.hash() % bkts.size();
		Bucket bkt = bkts[ind];

		for (int i = 0; i < bkt.size(); i++) {
			std::pair<Key, Val> &e = bkt[i];
			if (k == e.first)
				return true;
		}

		return false;
	}

	boost::optional<Val> find(Key k) {
		unsigned int ind = k.hash() % bkts.size();
		Bucket bkt = bkts[ind];

		for (int i = 0; i < bkt.size(); i++) {
			std::pair<Key, Val> &e = bkt[i];
			if (k == e.first)
				return boost::optional<Val>(e.second);
		}

		return boost::optional<Val>();
	}

	Val rm(Key k) {
		unsigned int ind = k.hash() % bkts.size();
		Bucket bkt = bkts[ind];

		for (int i = 0; i < bkt.size(); i++) {
			std::pair<Key, Val> &e = bkt[i];
			if (k == e.first) {
				Val res = e.second;

				if (i < bkt.size() - 1)
					bkt[i] = bkt[bkt.size() - 1];
				bkt.pop_back();
				fill--;

				return boost::optional<Val>(res);
			};
		}

		return boost::optional<Val>();
	}

private:
	typedef std::vector< std::pair<Key, Val> > Bucket;
	typedef std::vector<Bucket> Buckets;

	void grow(void) {
		Buckets b(bkts.size() * 2);

		for (int i = 0; i < bkts.size(); i++) {
			Bucket bkt = bkts[i];
			for (int j = 0; j < bkt.size(); j++) {
				std::pair<Key, Val> &e = bkt[j];
				unsigned int ind = e.first.hash() % b.size();
				b[ind].push_back(e);
			}
		}

		bkts = b;
	}

	unsigned int fill;
	Buckets bkts;
};