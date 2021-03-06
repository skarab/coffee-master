/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 *  CLZ �  �1.0    P   meta::ObjectPointer A<   5  	$   S    �R  graphics::Shader �A  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 0Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic:: H �F  Geometry"  Q�Fragment" &D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #B/�LineArray `String S  ��   #version 130 x ��   varying vec2 uv; 
    �3 view_vector; D  �void main()  { ��       uv = gl_MultiTexCoord0.xy; # ' g 0 �Color.xyz; ( �gl_Posit� �= ftransform(); � 4} � F/8 F"  < /< ��  Y   �P   - Qexten �GL_ARB_t��_rectangle : enable �5 �EXT_gpu_s�4/ � �// Default helpers  �� ��PackDepth(float d 5) � * 3~areturn2 / 2or(/ �/256.0, fract E); �|    m 5Unp � ~  ~ Z!   $~ ` 1.x*u + Uy); "o #o  ; � 3� qNormal( n 5) %n Z&   n % u+1.0; 'a (a )� a � c *c +c -c ,c -c T.   M��ComputeParallax(�,�3eyeE", bdheight `strengb/� 0�N fcamera�� Fize(_ )�1�  ; o # =s *l % -w  /2� 29uv+v S*h; 3d}    4T5   p@RGBEe4 v) 6� Y7   !� �exp = v.w*255.0-128�   	� p�*exp2(exp); 9�:� ;Ao#ifdef� n[� AAppl�2owsc��, sampler2DRect s" �lI�_softness,�5) =� >T�  / " = (B �>0.01); ?   H�� p*((1.0-/  )+ *� � (� �uv).x); @'A~�#endif B61C  g0uni�� �W ; D   &- �. E�. � p*3; Fw% `3; GK 2��me_size; H� IDJDKD LJ �*H83; N5 2   Om	>DSoft��eistancz), �P� O 0{ Q`
 a �radius =Q *	 
m&/(X1.y*p a/6.0);V 	Z # S�
k �stencil = �7; TW& @coun. 7; U1' 3or �i=-4.0 ; i<=	 �+=0.5) V   
5 w{ W   0 > m  @uv.x#R.y+i*C); X=8  3 �	@
{
�0, t�1z);nAQ � `ef = (��abs(i))*ddot(n,��>0.9); Z^I d!+=N  � ;�H �F ;; \O;} ]��� /@ 7; ^�:} _l`Xa�
 b: {QYc   D�) =�
� 	�� ude/�$uv�e�	O p�
G10; f<
� p � �

�.w)*10.0+ !*l�( Dxyz- H); g_h��Wi   ^�0gl_��+/4(� �� z�,� 14jR�#else k   1x 1A  �); l   K [m�no p�?q  ��\FlagsYH  @s   �u�P $wP �x   y   z) #+  ��FaceCullingMod1!EN��TATE_FACE_CULLINGv �FrontPolygon< 	�POLYGON_MODE< OBack; $�QTestE�sd bool � @Func@Z �TEST_FUNCTION[ Writing^ F � lW � L� lOQ  � Fa�[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real �v�|   ����}�~ ! ��� �$� � � � ��� ?� �� �?�  a #� � NType�PROPERTY_TYP�TValueL
��jEvalua�Q gEVALUA��� S�   ��t� ���S�   �u� ���S�   �ix� ��+S�   �� y� ��� S�   ��z� ��� S�   �+�/c  �
�v��nS���� ��I �	& + �<  � nRG B A �� � � &�  ��  ��& ' VuN2  � DX� Y � ��  5/-B
%) �?  � /� �� >XmeterC�TEXTURE_PARAMETER���-��� /coffee/import/� ts/null.� �g �5�5
�5�5��5�g �5 ,5 �	�4�4��4�g ��           