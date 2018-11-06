  #include<iostream>
  #include<fstream>
  #include<cstdlib>
  #include<string>
  #include<cmath>
  using namespace std;

  int base_change(string x, int k){
  int base_four = 0;
  for(int i = 0; i<k;i++){
  string substr = x.substr(k-i-1,1);
  int value = stoi(substr);
  base_four += value * pow(4, i);
  }
    return base_four;
  }
  string get_kmer(string x, int k){
    string to_return;
    for(int i=0;i<k;i++){
      char letter = x[i];
      switch (letter) {
        case '0':
        to_return+="A";
        break;
        case '1':
        to_return+="C";
        break;
        case '2':
        to_return+="G";
        break;
        case '3':
        to_return+="T";
        break;
      }
    }
    return to_return;
  }
  void histogram(const int* first, const int* last, int* const count, int m){
    for(int i=0;i<m;i++) count[i] =0;
    for(;first!=last;++first) {
      count[*first]++;
    }
  }



  int main(int argc, char const *argv[]) {
  ifstream file(argv[1]);
  int k = atoi(argv[2]) ;
  string s;
  getline(file, s);
  string stream2;
  int length =0;
  int size_A = 0;
  int size_C =0;
  int size_G = 0;
  int size_T = 0;
  int size_N = 0;
  for(auto i=0; i<s.length();i++){
  char c = s[i];
    switch (c) {
      case 'A':
      stream2.append("0");
      size_A +=1;
      length +=1;
      break;
      case 'C':
      stream2.append("1");
      length += 1;
      size_C +=1;
      break;
      case 'G':
      stream2.append("2");
      length += 1;
      size_G +=1;
      break;
      case 'T':
      stream2.append("3");
      length += 1;
      size_T +=1;
      break;
      case 'N':
    stream2.append("N");
     size_N +=1;
     length += 1;
     break;
    }

  }

  cout<<0<<" "<<k<<" "<<length<<"\n";
  cout<<1<<" "<<size_A<<" "<<size_C<<" "<<size_G<<" "<<size_T<<" "<<size_N<<"\n";
  if(length<k){
    cout<<"error"<<endl;
    return 0;
  }


//  length = length - size_N;


  int k_mer = length - k +1;
  if (k_mer <= 0 ){

    return 0;
  }
  int size = pow(4,k);
  string* kmer_holder = new string[k_mer];
  int* array_of_kmer = new int[k_mer] ;
  int countz = 0;
  for(int i =0; i<k_mer;i++){
  string index = (stream2.substr(i,k));
  if(index.find('N') == string::npos){
  int value = base_change(index,k);
  array_of_kmer[countz] = value;
  kmer_holder[countz] = index;
  countz++;
}
  }

  int* C = new int[size];
  //  histogram(array_of_kmer, array_of_kmer+k_mer, C, size);
  histogram(array_of_kmer, array_of_kmer+countz, C, size);
  const int* first = array_of_kmer;
  const int* last = array_of_kmer + countz;
  int counter = 0;
  for(;first!=last;++first){
 if(C[*first]!=0){
  string kmers = get_kmer(kmer_holder[counter],  k);
  cout<<kmers<<" "<<C[*first]<<"\n";
  C[*first] =0;
 }
  counter++;
  }





  delete[] array_of_kmer;
  delete[] C;
  delete[] kmer_holder;

    return 0;
  }
