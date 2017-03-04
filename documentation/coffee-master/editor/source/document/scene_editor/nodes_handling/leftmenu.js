function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6479\" class=\"headerLeftMenuInActive\"><a id=\"aID6479\" href=\"#\" OnMouseOver=\"link('_dir','nodes_handling0',this)\" class=\"leftMenuLinkHeadInActive\">nodes_handling</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6177\" class=\"leftMenuInActive\"><a id=\"aID6177\" href=\"#\" OnMouseOver=\"link('_class','ApplicationCommand0',this)\" class=\"leftMenuLinkInActive\">ApplicationCommand</a></div>\n");
document.write("<div id=\"divID6176\" class=\"leftMenuInActive\"><a id=\"aID6176\" href=\"#\" OnMouseOver=\"link('_class','PluginNodeController0',this)\" class=\"leftMenuLinkInActive\">PluginNodeController</a></div>\n");
document.write("<div id=\"divID1076\" class=\"leftMenuInActive\"><a id=\"aID1076\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorAddNode38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorAddNode</a></div>\n");
document.write("<div id=\"divID1077\" class=\"leftMenuInActive\"><a id=\"aID1077\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorAttachNode38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorAttachNode</a></div>\n");
document.write("<div id=\"divID1078\" class=\"leftMenuInActive\"><a id=\"aID1078\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorCloseNode38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorCloseNode</a></div>\n");
document.write("<div id=\"divID1079\" class=\"leftMenuInActive\"><a id=\"aID1079\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorDetachNode38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorDetachNode</a></div>\n");
document.write("<div id=\"divID1080\" class=\"leftMenuInActive\"><a id=\"aID1080\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorGroupNodes38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorGroupNodes</a></div>\n");
document.write("<div id=\"divID1081\" class=\"leftMenuInActive\"><a id=\"aID1081\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorInstantiate38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorInstantiate</a></div>\n");
document.write("<div id=\"divID1082\" class=\"leftMenuInActive\"><a id=\"aID1082\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorNodeController38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorNodeController</a></div>\n");
document.write("<div id=\"divID1083\" class=\"leftMenuInActive\"><a id=\"aID1083\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorOpenNode38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorOpenNode</a></div>\n");
document.write("<div id=\"divID1084\" class=\"leftMenuInActive\"><a id=\"aID1084\" href=\"#\" OnMouseOver=\"link('_class','SceneEditorSetRootUndo38803',this)\" class=\"leftMenuLinkInActive\">SceneEditorSetRootUndo</a></div>\n");
document.write("<div id=\"divID6186\" class=\"leftMenuInActive\"><a id=\"aID6186\" href=\"#\" OnMouseOver=\"link('_class','UndoObject0',this)\" class=\"leftMenuLinkInActive\">UndoObject</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
