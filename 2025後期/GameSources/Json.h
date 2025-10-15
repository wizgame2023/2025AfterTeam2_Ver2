/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	enum class JsonType {
		Number, String, Bool, Object, Array, Null, Unknown
	};

	class JsonValue {
	protected:
		/// <summary>
		/// �o�͎��Ɏw�肵�����̃C���f���g��ǉ�
		/// </summary>
		/// <param name="indent">�C���f���g�[�x</param>
		/// <param name="str">������(�Q��)</param>
		void Indent(int indent,wstring& str) {
			for (int i = 0; i < indent; i++) {
				str += L"\t";
			}
		}
	public:
		virtual ~JsonValue() {}
		virtual JsonType GetType()const { return JsonType::Unknown; }
		virtual wstring ToString(int indent = 0) { return L""; }

		bool CompareType(JsonType type) const {
			return GetType() == type;
		}

		/// <summary>
		/// shared_ptr�ɕϊ��B�X���C�X�΍�
		/// </summary>
		/// <returns>shared_ptr</returns>
		virtual shared_ptr<JsonValue> Clone()const {
			return make_shared<JsonValue>(*this);
		}
	};

	class JsonNumber : public JsonValue {
		float m_Value;
	public:
		JsonNumber(float value) :m_Value(value) {}
		virtual JsonType GetType() const override { return JsonType::Number; }
		virtual shared_ptr<JsonValue> Clone()const override {
			return make_shared<JsonNumber>(*this);
		}
		virtual wstring ToString(int indent = 0)override {
			return to_wstring(m_Value);
		}

		/// <summary>
		/// �l��float�^�Ŏ擾
		/// </summary>
		/// <returns>float</returns>
		float GetFloatValue() const { return m_Value; }

		/// <summary>
		/// �l��int�^�Ŏ擾
		/// </summary>
		/// <returns>int</returns>
		int GetIntValue() const { return static_cast<int>(m_Value); }
	};

	class JsonString : public JsonValue {
		wstring m_Value;
	public:
		JsonString(const wstring& value) :m_Value(value) {}
		virtual JsonType GetType() const override { return JsonType::String; }
		virtual shared_ptr<JsonValue> Clone()const override {
			return make_shared<JsonString>(*this);
		}
		virtual wstring ToString(int indent = 0) override {
			return L"\"" + m_Value + L"\"";
		}

		const wstring& GetValue() const { return m_Value; }
	};

	class JsonBool : public JsonValue {
		bool m_Value;
	public:
		JsonBool(bool value) :m_Value(value) {}
		virtual JsonType GetType() const override { return JsonType::Bool; }
		virtual shared_ptr<JsonValue> Clone()const override {
			return make_shared<JsonBool>(*this);
		}
		virtual wstring ToString(int indent = 0) override {
			return m_Value ? L"true" : L"false";
		}

		bool GetValue() const { return m_Value; }
	};
	class JsonNull : public JsonValue {
		public:
		JsonNull() {}
		virtual JsonType GetType() const override { return JsonType::Null; }
	};
	
	class JsonObject;
	class JsonArray : public JsonValue {
		JsonType m_ArrayType;

	public:
		vector<shared_ptr<JsonValue>> m_Values;

		JsonArray() : m_ArrayType(JsonType::Unknown) {}
    //---------�z��̏�����----------
	//    std::variant�g������

		JsonArray(const vector<int>& array);
		JsonArray(const vector<float>& array);
		JsonArray(const vector<bool>& array);
		JsonArray(const vector<wstring>& array);
		JsonArray(const vector<JsonObject>& array);

		virtual JsonType GetType() const override { return JsonType::Array; }
		virtual shared_ptr<JsonValue> Clone()const override {
			return make_shared<JsonArray>(*this);
		}
		virtual wstring ToString(int indent = 0)override {
			wstring str = L"[";
			for (auto it = m_Values.begin(); it != m_Values.end(); it++) {
				auto value = *it;
				str += value->ToString(indent);

				if (next(it) != m_Values.end()) {
					str += L",";
				}
			}
			str += L"]";

			return str;
		}

		vector<int> GetIntArray();
		vector<float> GetFloatArray();
		vector<bool> GetBoolArray();
		vector<wstring> GetStringArray();
		vector<shared_ptr<JsonObject>> GetObjectArray();

		/// <summary>
		/// �z��ɒl��ǉ�
		/// �قȂ�^��ǉ����悤�Ƃ����ꍇ�̓G���[
		/// </summary>
		/// <param name="value">�l</param>
		void Add(const JsonValue& value) {
			Add(value.Clone());
		}

		/// <summary>
		/// �z��ɒl��ǉ�
		/// �قȂ�^��ǉ����悤�Ƃ����ꍇ�̓G���[
		/// </summary>
		/// <param name="value">�l�̃|�C���^�[</param>
		void Add(const shared_ptr<JsonValue>& value) {
			if (!m_Values.empty()) {
				if (!value->CompareType(m_Values[0]->GetType())) {
					throw BaseException(L"�قȂ�^��z��Ɋ܂߂邱�Ƃ͂ł��܂���",L"", L"JsonArray::Add(const shared_ptr<JsonValue>&)");
				}
			}
			else {
				m_ArrayType = value->GetType();
			}
			m_Values.push_back(value);
		}
	};
	struct ObjectData;

	class JsonObject : public JsonValue {
		map<wstring, shared_ptr<JsonValue>> m_Values;

	public:
		JsonObject() {}
		JsonObject(initializer_list<ObjectData> list);
		virtual JsonType GetType() const override { return JsonType::Object; }
		virtual shared_ptr<JsonValue> Clone()const override {
			return make_shared<JsonObject>(*this);
		}
		virtual wstring ToString(int indent = 0)override {
			wstring str = L"{\n";

			for (auto it = m_Values.begin(); it != m_Values.end(); it++) {
				Indent(indent, str);
				auto value = *it;
				str += L"\"" + value.first + L"\" : " + value.second->ToString(indent + 1);
				if (next(it) != m_Values.end()) {
					str += L",\n";
				}
			}
			str += L"\n";
			Indent(indent - 1, str);
			str += L"}";

			return str;
		}

		/// <summary>
		/// �w�肳�ꂽ�L�[�����݂��邩����
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <returns>���茋��</returns>
		bool HasKey(const wstring& key) const {
			return m_Values.find(key) != m_Values.end();
		}

		/// <summary>
		/// �w�肳�ꂽ�L�[�̒l��JsonValue�^�Ŏ擾(���݂��Ȃ��ꍇ�̓G���[)
		/// </summary>
		/// <param name="key"></param>
		/// <returns>�l(JsonValue�^)</returns>
		inline shared_ptr<JsonValue> At(const wstring& key) {
			auto it = m_Values.find(key);
			if (it != m_Values.end()) {
				return it->second;
			}
			else {
				throw BaseException(L"�L�[�����݂��܂���", key, L"JsonObject::At(const wstring&)");
			}
		}

		/// <summary>
		/// �w�肳�ꂽ�L�[�̒l���w�肳�ꂽ�^�Ŏ擾(���݂��Ȃ��ꍇ�̓G���[)
		/// </summary>
		/// <typeparam name="T">�^</typeparam>
		/// <param name="key">�L�[</param>
		/// <returns>�l(T�^)</returns>
		template<class T>
		inline shared_ptr<T> At(const wstring& key) {
			auto value = At(key);
			auto casted = dynamic_pointer_cast<T>(value);
			if(!casted) throw BaseException(L"�^���قȂ�܂�", key + L"/" + Util::GetWSTypeName<T>(),L"JsonObject::At<T>(const wstring&)");
			return casted;
		}

		/// <summary>
		/// �w�肵���L�[�̒l��ݒ�(���݂��Ȃ��ꍇ�͒ǉ�)
		/// ���ɑ��݂���ꍇ�͏㏑�������
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <param name="value">�l</param>
		inline void Set(const wstring& key, const shared_ptr<JsonValue>& value) {
			m_Values[key] = value;
		}

		/// <summary>
		/// �w�肵���L�[�ƒl��ǉ�
		/// �㏑���͂ł��Ȃ�(�G���[)
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <param name="value">�l</param>
		/// <returns>�ǉ������l</returns>
		inline shared_ptr<JsonValue> Add(const wstring& key, const JsonValue& value) {
			return Add(key, value.Clone());
		}
		/// <summary>
		/// �w�肵���L�[�ƒl��ǉ�
		/// �㏑���͂ł��Ȃ�(�G���[)
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <param name="value">�l�̃|�C���^�[</param>
		/// <returns>�ǉ������l</returns>
		inline shared_ptr<JsonValue> Add(const wstring& key, const shared_ptr<JsonValue>& value) {
			if (HasKey(key)) {
				throw BaseException(L"�L�[�����łɑ��݂��܂�", key, L"JsonObject::Add(const wstring&, const shared_ptr<JsonValue>&)");
			}
			m_Values[key] = value;

			return value;
		}

		/// <summary>
		/// �o�^����Ă���L�[���擾
		/// </summary>
		/// <returns>�L�[�z��</returns>
		inline vector<wstring> GetKeys() const {
			vector<wstring> keys;
			for (auto& pair : m_Values) {
				keys.push_back(pair.first);
			}
			return keys;
		}
	};
//---------�f�[�^�ƃt�@�C���f�[�^�̕ϊ�������N���X----------
//       Json�N���X���Ŏg�p�����
	class JsonHelper {
	//----------���l�ϊ�----------
		
		/// <summary>
		/// �����񂩂�l�̃f�[�^�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonValue> ParseValue(const wstring& str, size_t& pos);

		/// <summary>
		/// �����񂩂�l�̃f�[�^(int�Afloat)�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonNumber> ParseNumber(const wstring& str, size_t& pos);

		/// <summary>
		/// �����񂩂�l�̃f�[�^(bool)�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonBool> ParseBool(const wstring& str, size_t& pos);

		/// <summary>
		/// �����񂩂�l�̃f�[�^(������)�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonString> ParseString(const wstring& str, size_t& pos);

		/// <summary>
		/// �����񂩂�l�̃f�[�^(�z��)�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonArray> ParseArray(const wstring& str, size_t& pos);

		/// <summary>
		/// �����񂩂�l�̃f�[�^(�I�u�W�F�N�g)�ɕϊ�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		/// <returns>�l</returns>
		shared_ptr<JsonObject> ParseObject(const wstring& str, size_t& pos);

	//----------�����񑀍�----------

		/// <summary>
		/// �J�n�n�_���玟�̕����܂ł̋󔒂��X�L�b�v
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�J�n�ʒu</param>
		void SkipSpace(const wstring& str, size_t& pos) {
			while (isspace(Peek(str, pos))) Get(str, pos);
		}

		/// <summary>
		/// �w�肳�ꂽ�ʒu�̕������擾
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�ʒu</param>
		/// <returns>����</returns>
		wchar_t Peek(const wstring& str, size_t& pos) {
			if (pos >= str.size()) return L'\0';
			return str[pos];
		}

		/// <summary>
		/// �w�肳�ꂽ�ʒu�̕������擾���A�ʒu��1�i�߂�
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="pos">�ʒu</param>
		/// <returns>����</returns>
		wchar_t Get(const wstring& str, size_t& pos) {
			if (pos >= str.size()) return L'\0';
			return str[pos++];
		}
	public:
		/// <summary>
		/// JsonObject�^�̃f�[�^���t�@�C���ɕۑ�����
		/// </summary>
		/// <param name="filename">�ۑ���</param>
		/// <param name="data">�f�[�^</param>
		void ParseFile(const wstring& filename,const shared_ptr<JsonObject>& data);

		/// <summary>
		/// �t�@�C����ǂݍ����JsonObject�^�̃f�[�^�ɕϊ�����
		/// </summary>
		/// <param name="filename">�Q�Ɛ�</param>
		/// <returns>�f�[�^</returns>
		shared_ptr<JsonObject> ParseValue(const wstring& filename);

		/// <summary>
		/// �p�X���L�[�ɕϊ�����
		/// </summary>
		/// <param name="root">���[�g�p�X</param>
		/// <returns>�L�[</returns>
		vector<wstring> SplitKey(const wstring& root);

		/// <summary>
		/// �p�X�����ǂ�B�Ȃ��ꍇ�͐V�����쐬�����
		/// </summary>
		/// <param name="keys">�L�[�̔z��</param>
		/// <returns>���ǂ�������</returns>
		shared_ptr<JsonObject> EnsurePath(const vector<wstring>& keys,shared_ptr<JsonObject>& root);
	};

//---------Json�̃f�[�^�Ǘ����s���N���X----------
//       ���ۂɎg���ۂ͂��̃N���X��錾����
	class Json {
		shared_ptr<JsonObject> m_Root;	//�f�[�^�{��
		JsonHelper m_Helper;	//�ϊ��⏕

		static wstring s_DefaultFilePath; //�f�t�H���g�̃t�@�C����
	public:
		static void SetDefaultFilePath(const wstring& path) { s_DefaultFilePath = path; }

		Json() :m_Root(make_shared<JsonObject>()) {
			m_Helper = JsonHelper();
		}
		/// <summary>
		/// �쐬�ƂƂ��Ƀt�@�C����ǂݍ��ރR���X�g���N�^
		/// </summary>
		/// <param name="filename">�t�@�C����</param>
		Json(const wstring& filename) {
			m_Helper = JsonHelper();
			Load(filename);
		}

		shared_ptr<JsonObject> GetRoot() const { return m_Root; }

		/// <summary>
		/// �w�肳�ꂽ�t�@�C������f�[�^��ǂݍ���
		/// </summary>
		/// <param name="filename">�t�@�C����</param>
		void Load(const wstring& filename) {
			m_Root = m_Helper.ParseValue(s_DefaultFilePath + filename);
		}

		/// <summary>
		/// �w�肳�ꂽ�t�@�C�����Ńf�[�^��ۑ����܂��B
		/// </summary>
		/// <param name="filename">�ۑ���̃t�@�C����</param>
		void Save(const wstring& filename) {
			m_Helper.ParseFile(s_DefaultFilePath + filename, m_Root);
		}

		/// <summary>
		/// �w�肳�ꂽ�p�X�E�L�[�ɒl��ݒ�
		/// </summary>
		/// <param name="root">�p�X</param>
		/// <param name="value">�l�̃|�C���^�[</param>
		void Set(const wstring& root, const shared_ptr<JsonValue>& value);

		/// <summary>
		/// �w�肳�ꂽ�p�X�E�L�[�ɒl��ݒ�
		/// </summary>
		/// <param name="root">�p�X</param>
		/// <param name="value">�l</param>
		void Set(const wstring& root, const JsonValue& value) {
			Set(root, value.Clone());
		}

		/// <summary>
		/// �w�肳�ꂽ�p�X�ɐݒ肳�ꂽ�l��JsonValue�^�Ŏ擾
		/// </summary>
		/// <param name="root">�p�X</param>
		/// <returns>�l(JsonValue�^)</returns>
		shared_ptr<JsonValue> At(const wstring& root);

		/// <summary>
		/// �w�肳�ꂽ�p�X�ɐݒ肳�ꂽ�l���w�肳�ꂽ�^�Ŏ擾
		/// </summary>
		/// <typeparam name="T">�擾�^</typeparam>
		/// <param name="root">�p�X</param>
		/// <returns>�l(T�^)</returns>
		template <class T>
		shared_ptr<T> At(const wstring& root) {
			return dynamic_pointer_cast<T>(At(root));
		}

		/// <summary>
		/// �w�肵���L�[�ɑΉ�����l���擾�B
		/// ����g���Â炢�BAt<T>���g���ׂ��B
		/// virant���g�킹��
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <returns>�l</returns>
		inline shared_ptr<JsonValue> operator[](const wstring& key) {
			if (!m_Root->HasKey(key)) {
				throw BaseException(L"�w�肵���L�[�����݂��܂���",key, L"Json::operator[](const wstring&)");
			}
			return m_Root->At(key);
		}
	};
}
//end basecross
