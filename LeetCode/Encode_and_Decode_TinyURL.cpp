class Solution {
public:
    map<string, string> table;
    int key = 0;
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string tiny = "http://a.com/" + std::to_string(key++);
        table[tiny] = longUrl;
        return tiny;
    }
    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return table[shortUrl];
    }
};
// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));