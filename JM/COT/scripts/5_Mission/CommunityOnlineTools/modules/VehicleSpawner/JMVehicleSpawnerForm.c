class JMVehicleSpawnerForm extends JMFormBase
{
	protected Widget m_ActionsWrapper;

	protected ref array< ref UIActionButton > m_VehicleButtons;

	void JMVehicleSpawnerForm()
	{
		m_VehicleButtons = new array< ref UIActionButton >;
	}

	void ~JMVehicleSpawnerForm()
	{
	}

	override void OnInit()
	{
		m_ActionsWrapper = layoutRoot.FindAnyWidget( "actions_wrapper" );
	}

	override void OnShow()
	{
		JMVehicleSpawnerModule gm = JMVehicleSpawnerModule.Cast( module );

		if ( gm == NULL )
			return;

		for ( int i = 0; i < gm.GetVehicles().Count(); i++ )
		{
			string name = gm.GetVehicles()[i];

			UIActionButton button = UIActionManager.CreateButton( m_ActionsWrapper, "Spawn " + name + " at Cursor", this, "SpawnVehicle" );
			button.SetData( new JMVehicleSpawnerButtonData( name ) );

			m_VehicleButtons.Insert( button );
		}
	}

	override void OnHide() 
	{
		for ( int j = 0; j < m_VehicleButtons.Count(); j++ )
		{
			if ( m_VehicleButtons[j].GetLayoutRoot() )
			{
				m_ActionsWrapper.RemoveChild( m_VehicleButtons[j].GetLayoutRoot() );
			}
		}

		m_VehicleButtons.Clear();
	}

	void SpawnVehicle( UIEvent eid, ref UIActionBase action ) 
	{
		JMVehicleSpawnerButtonData data;
		if ( !Class.CastTo( data, action.GetData() ) )
			return;

		JMVehicleSpawnerModule mod;
		if ( !Class.CastTo( mod, module ) )
			return;

		mod.SpawnPosition( data.ClassName, GetCursorPos() );
	}
}