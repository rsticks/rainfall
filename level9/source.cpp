#include <cstring>
#include <cstdlib>


class N
{
private:
    char    annotation[100];
    int     number;
public:
    N(int n): number(n) {}
	void    setAnnotation(const char *str) {
	    memcpy(this->annotation, str, strlen(str));
	}
	int     operator+(N& rhs) {
		return (this->number + rhs.number);
	}
	int     operator-(N& rhs) {
		return (this->number - rhs.number);
	}
};


int		main(int argc, char **argv)
{
	if (argc < 1)
	    _exit(1);

	N *a = new N(5);
	N *b = new N(6);

	a->setAnnotation(argv[1]);
	return (b->*(b->func))(*a);
}
