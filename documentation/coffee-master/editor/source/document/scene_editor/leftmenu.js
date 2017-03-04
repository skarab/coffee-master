function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6480\" class=\"headerLeftMenuInActive\"><a id=\"aID6480\" href=\"#\" OnMouseOver=\"link('_dir','scene_editor0',this)\" class=\"leftMenuLinkHeadInActive\">scene_editor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6479\" class=\"leftMenuInActive\"><a id=\"aID6479\" href=\"#\" OnMouseOver=\"link('_dir','nodes_handling/nodes_handling0',this)\" class=\"leftMenuLinkInActive\">nodes_handling</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1085\" class=\"leftMenuInActive\"><a id=\"aID1085\" href=\"#\" OnMouseOver=\"link('_class','SceneEditor38803',this)\" class=\"leftMenuLinkInActive\">SceneEditor</a></div>\n");
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
