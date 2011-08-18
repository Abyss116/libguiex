<?xml version="1.0" ?>
<guiex>
	<property name="grass_lower" type="CGUIImageDefine">
		<property  name="path" type="CGUIString" value="image/grass_lower.tga" />
		<property name="uv" type="CGUIRect" value="0,0,1024,384" />
		<property name="size" type="CGUISize" value="1024,384" />
	</property>

	<property name="grass_upper" type="CGUIImageDefine">
		<property  name="path" type="CGUIString" value="image/grass_upper.tga" />
		<property name="uv" type="CGUIRect" value="0,0,1024,384" />
		<property name="size" type="CGUISize" value="1024,384" />
	</property>

	<property name="bg_dirt" type="CGUIImageDefine">
		<property  name="path" type="CGUIString" value="image/bg_dirt.tga" />
		<property name="uv" type="CGUIRect" value="0,0,512,384" />
		<property name="size" type="CGUISize" value="512,384" />
	</property>


	<!-- animation's image -->
	<property name="mole_laugh_1" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_laugh1.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>
	<property name="mole_laugh_2" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_laugh2.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>
	<property name="mole_laugh_3" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_laugh3.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>	
	<property name="mole_thump_1" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_thump1.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>
	<property name="mole_thump_2" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_thump2.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>
	<property name="mole_thump_3" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_thump3.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>
	<property name="mole_thump_4" type="CGUIImageDefine">
		<property name="path" type="CGUIString" value="image/anim/mole_thump4.tga" />
		<property name="uv" type="CGUIRect" value="0,0,178,200" />
		<property name="size" type="CGUISize" value="178,200"/>
	</property>


	<property name="mole_laugh" type="CGUIAnimationDefine">
		<property name="size" type="CGUISize" value="178,200"/>
		<property name="interval" type="real" value="0.2"/>
		<property name="loop" type="bool" value="false"/>
		<property name="images" type="array" >
			<property name="image" type="CGUIImage" value="mole_laugh_1" />
			<property name="image" type="CGUIImage" value="mole_laugh_2" />
			<property name="image" type="CGUIImage" value="mole_laugh_3" />
		</property>
	</property>

	<property name="mole" type="CGUIAnimationDefine">
		<property name="size" type="CGUISize" value="178,200"/>
		<property name="loop" type="bool" value="false"/>
		<property name="interval" type="real" value="0.2"/>
		<property name="images" type="array" >
			<property name="image" type="CGUIImage" value="mole_laugh_1" />
		</property>
	</property>

	<property name="mole_thump" type="CGUIAnimationDefine">
		<property name="size" type="CGUISize" value="178,200"/>
		<property name="interval" type="real" value="0.2"/>
		<property name="loop" type="bool" value="false"/>
		<property name="images" type="array" >
			<property name="image" type="CGUIImage" value="mole_thump_1" />
			<property name="image" type="CGUIImage" value="mole_thump_2" />
			<property name="image" type="CGUIImage" value="mole_thump_3" />
			<property name="image" type="CGUIImage" value="mole_thump_4" />
		</property>
	</property>

</guiex>



