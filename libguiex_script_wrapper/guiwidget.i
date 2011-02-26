namespace guiex
{
	class CGUIWidget
	{
	public:
		bool IsCreate() const;

		virtual void Open();
		bool IsOpen() const;
		virtual void Close();

		// tree function
		void SetParent( CGUIWidget *pParent);
		CGUIWidget* GetParent()  const;
		CGUIWidget* GetChild( ) const;
		CGUIWidget* GetChild( const CGUIString& rChildName ) const;
		CGUIWidget* GetNextSibling( ) const;
		//CGUIWidget* GetExclusiveChild( ) const;

		void MoveToTop();
		void MoveDown();
		void MoveUp();

		const CGUIString& GetName() const;
		const CGUIString& GetSceneName( ) const;

		const CGUIString& GetWorkingSceneName( ) const;

		const CGUIString& GetType() const;

		void SetUserData(void* pData);
		void* GetUserData() const;

		////////////////////////////////////////////////////////////////////////////
		// text about function
		////////////////////////////////////////////////////////////////////////////
		virtual void SetTextColor(const CGUIColor& rColor);
		virtual bool IsTextContentEmpty( ) const;
		void SetTextContentUTF8( const CGUIString& rString);
		CGUIString GetTextContentUTF8() const;

		////////////////////////////////////////////////////////////////////////////
		// flag
		////////////////////////////////////////////////////////////////////////////
		void SetAutoPlayAs( bool bEnable );
		bool IsAutoPlayAs( ) const;

		void SetClipChildren( bool bClip );
		bool IsClipChildren( ) const;

		void SetActivable(bool bActivable);
		bool IsActivable() const;
		bool IsDerivedActivable();

		void SetFocus(bool bFocus);
		bool IsFocus() const;

		void SetVisible(bool bVisible);
		bool IsVisible( ) const;
		bool IsDerivedVisible();

		void SetDisable(bool bDisable);
		bool IsDisable( ) const;
		bool IsDerivedDisable();

		void SetAlpha( real fAlpha );
		real GetAlpha()  const;
		real GetDerivedAlpha();

		void SetScale( const CGUISize& );
		const CGUISize& GetScale() const;
		const CGUISize& GetDerivedScale();

		void SetColor(const CGUIColor& rColor );
		const CGUIColor& GetColor() const;

		CGUIWidget* GetWidgetAtPoint(const CGUIVector2& rPos);
		virtual bool HitTest( const CGUIVector2& rPos);

		////////////////////////////////////////////////////////////////////////////
		// resource related operation
		////////////////////////////////////////////////////////////////////////////
		CGUIImage* SetImage( const CGUIString& rName, const CGUIString& rImageName );
		void SetImage( const CGUIString& rName, CGUIImage* pImage );
		bool HasImage( const CGUIString& rName );
		CGUIImage* GetImage( const CGUIString& rName );

		void SetAnimation( const CGUIString& rName, CGUIAnimation* pAnimation );
		CGUIAnimation* SetAnimation( const CGUIString& rName, const CGUIString& rAnimationName );
		CGUIAnimation* GetAnimation( const CGUIString& rAnimationName);

		CGUIAs* SetAs( const CGUIString& rName, const CGUIString& rAsName );
		void SetAs( const CGUIString& rName, CGUIAs* pAs );
		bool HasAs( const CGUIString& rName );
		CGUIAs* GetAs( const CGUIString& rName );

		void PlayAs( const CGUIString& rName );
		void PlayAs( CGUIAs* pAs );
		bool IsAsPlaying( const CGUIString& rName );
		bool IsAsPlaying( CGUIAs* pAs );
		void StopAs( const CGUIString& rName );
		void StopAs( CGUIAs* pAs );
		void StopAll( );

		////////////////////////////////////////////////////////////////////////////
		// property related operation
		////////////////////////////////////////////////////////////////////////////
		void SetProperty( const CGUIProperty& rProperty);
		const CGUIProperty& GetProperty() const;
		void ClearProperty();
		void InsertProperty( const CGUIProperty& rProperty);
		void LoadFromProperty();
		void DumpToProperty();
		virtual int32 GenerateProperty( CGUIProperty& rProperty );
		virtual void ProcessProperty( const CGUIProperty& rProperty);

	public:
		void RegisterScriptCallbackFunc( const CGUIString& strEventName, const CGUIString& strFunc );
		void UnregisterScriptCallbackFunc(const CGUIString& strEventName);
		bool HasScriptCallbackFunc(const CGUIString& strEventName) const;
		const CGUIString& GetScriptCallbackFunc(const CGUIString& strEventName) const;

		void SetPosition( real x, real y );
		void SetPosition( const CGUIVector2&rPos );
		const CGUIVector2& GetPosition() const; 
		void SetPixelPosition( const CGUIVector2& rPixelPos );
		void SetPixelPosition( real x, real y );
		const CGUIVector2& GetPixelPosition() const;

		void SetPositionType( EScreenValue rValueType );
		EScreenValue GetPositionType( ) const; 

		void SetSize( real width, real height );
		void SetSize( const CGUISize& rSize );
		const CGUISize&	GetSize() const;
		void SetPixelSize( real width, real height );
		void SetPixelSize( const CGUISize& rPixelSize );
		const CGUISize&	GetPixelSize() const;

		void SetSizeType( EScreenValue eValueType );
		EScreenValue GetSizeType( ) const;

		void SetRotation(real x, real y, real z);
		void SetRotation(const CGUIVector3& rRotation);
		const CGUIVector3& GetRotation( ) const;

		void LocalToWorld( CGUIVector2& rPos );
		void WorldToLocal( CGUIVector2& rPos );

		void LocalToWorld( CGUIVector3& rPos );
		void WorldToLocal( CGUIVector3& rPos );

		void ParentToWorld( CGUIVector2& rPos );
		void WorldToParent( CGUIVector2& rPos );

		void ParentToLocal( CGUIVector2& rPos );
		void LocalToParent( CGUIVector2& rPos );


		const CGUIVector2& GetAnchorPoint();
		void SetAnchorPoint(const CGUIVector2&rAnchorPoint);
		void SetAnchorPoint(real x, real y);

		void SetMaximumSize(const CGUISize& rSize);	
		const CGUISize&	 GetMaximumSize() const;	
		void SetMinimumSize(const CGUISize& rSize);	
		const CGUISize&	GetMinimumSize() const;		

		void SetOpenWithParent( bool bFlag ); 
		bool IsOpenWithParent( ) const;

		void SetInheritAlpha( bool bFlag ); 
		bool IsInheritAlpha( ) const;

		void SetFocusAgency( bool bFlag ); 
		bool IsFocusAgency( ) const;

		void SetFocusable( bool bFlag ); 
		bool IsFocusable( ) const;
		bool IsDerivedFocusable( ) const;

		void SetMovable( bool bFlag ); 
		bool IsMovable( ) const;

		void SetHitable( bool bFlag ); 
		bool IsHitable( ) const;

		void SetMouseConsumed( bool bFlag ); 
		bool IsMouseConsumed( ) const;

		void SetResponseParentSizeChangeEvent( bool bFlag ); 
		bool IsResponseParentSizeChangeEvent( ) const;

		void SetResponseUpdateEvent( bool bFlag ); 
		bool IsResponseUpdateEvent( ) const;

		void SetGenerateClickEvent( bool bFlag ); 
		bool IsGenerateClickEvent( ) const;

		void SetGenerateDBClickEvent( bool bFlag ); 
		bool IsGenerateDBClickEvent( ) const;

		void SetGenerateMultiClickEvent( bool bFlag ); 
		bool IsGenerateMultiClickEvent( ) const;

	protected:
		CGUIWidget();
		virtual ~CGUIWidget();
	};




	//============================================================================//
	// CGUIWgtCheckButton
	//============================================================================// 
	class CGUIWgtCheckButton : public CGUIWidget
	{
	public:
	};


	//============================================================================//
	// CGUIWgtRadioButton
	//============================================================================// 
	class CGUIWgtRadioButton : public CGUIWgtCheckButton
	{
	public:
	};


	//============================================================================//
	// CGUIWgtRadioButton
	//============================================================================// 
	class CGUIWgtButton : public CGUIWidget
	{
	public:
	};

	//============================================================================//
	// CGUIWgtEmptyNode
	//============================================================================// 
	class CGUIWgtEmptyNode : public CGUIWidget
	{
	};


	//============================================================================//
	// CGUIWgtPanel
	//============================================================================// 
	class CGUIWgtPanel : public CGUIWidget
	{
	};


	//============================================================================//
	// CGUIWgtStaticImage
	//============================================================================// 
	class CGUIWgtStatic : public CGUIWidget
	{
	};


	//============================================================================//
	// CGUIWgtStaticImage
	//============================================================================// 
	class CGUIWgtStaticImage : public CGUIWgtStatic
	{
	};

	//============================================================================//
	// CGUIWgtStaticText
	//============================================================================// 
	class CGUIWgtStaticText : public CGUIWgtStatic
	{
	};

	//============================================================================//
	// CGUIWgtEditBox
	//============================================================================// 
	class CGUIWgtEditBox : public CGUIWidget
	{
	};


	//============================================================================//
	// CGUIWgtScrollbar
	//============================================================================// 
	//class CGUIWgtScrollbar : public CGUIWidget
	//{
	//public:

	//};


	//============================================================================//
	// CGUIWgtScrollPanel
	//============================================================================// 
	//class CGUIWgtScrollPanel : public CGUIWidget
	//{
	//public:

	//};
}
