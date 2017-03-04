function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6508\" class=\"headerLeftMenuInActive\"><a id=\"aID6508\" href=\"#\" OnMouseOver=\"link('_dir','wide0',this)\" class=\"leftMenuLinkHeadInActive\">wide</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6411\" class=\"leftMenuInActive\"><a id=\"aID6411\" href=\"#\" OnMouseOver=\"link('_dir','application/application0',this)\" class=\"leftMenuLinkInActive\">application</a></div>\n");
document.write("<div id=\"divID6415\" class=\"leftMenuInActive\"><a id=\"aID6415\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6419\" class=\"leftMenuInActive\"><a id=\"aID6419\" href=\"#\" OnMouseOver=\"link('_dir','edition/edition0',this)\" class=\"leftMenuLinkInActive\">edition</a></div>\n");
document.write("<div id=\"divID6425\" class=\"leftMenuInActive\"><a id=\"aID6425\" href=\"#\" OnMouseOver=\"link('_dir','plugins/plugins0',this)\" class=\"leftMenuLinkInActive\">plugins</a></div>\n");
document.write("<div id=\"divID6426\" class=\"leftMenuInActive\"><a id=\"aID6426\" href=\"#\" OnMouseOver=\"link('_dir','project/project0',this)\" class=\"leftMenuLinkInActive\">project</a></div>\n");
document.write("<div id=\"divID6442\" class=\"leftMenuInActive\"><a id=\"aID6442\" href=\"#\" OnMouseOver=\"link('_dir','ui/ui0',this)\" class=\"leftMenuLinkInActive\">ui</a></div>\n");
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
