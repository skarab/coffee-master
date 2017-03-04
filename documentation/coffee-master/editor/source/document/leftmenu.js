function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6478\" class=\"headerLeftMenuInActive\"><a id=\"aID6478\" href=\"#\" OnMouseOver=\"link('_dir','document0',this)\" class=\"leftMenuLinkHeadInActive\">document</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6480\" class=\"leftMenuInActive\"><a id=\"aID6480\" href=\"#\" OnMouseOver=\"link('_dir','scene_editor/scene_editor0',this)\" class=\"leftMenuLinkInActive\">scene_editor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1075\" class=\"leftMenuInActive\"><a id=\"aID1075\" href=\"#\" OnMouseOver=\"link('_class','Document38803',this)\" class=\"leftMenuLinkInActive\">Document</a></div>\n");
document.write("<div id=\"divID6204\" class=\"leftMenuInActive\"><a id=\"aID6204\" href=\"#\" OnMouseOver=\"link('_class','Plugin0',this)\" class=\"leftMenuLinkInActive\">Plugin</a></div>\n");
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
