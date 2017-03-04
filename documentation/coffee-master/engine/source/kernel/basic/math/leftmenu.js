function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6505\" class=\"headerLeftMenuInActive\"><a id=\"aID6505\" href=\"#\" OnMouseOver=\"link('_dir','math0',this)\" class=\"leftMenuLinkHeadInActive\">math</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6282\" class=\"leftMenuInActive\"><a id=\"aID6282\" href=\"#\" OnMouseOver=\"link('_dir','angle/angle0',this)\" class=\"leftMenuLinkInActive\">angle</a></div>\n");
document.write("<div id=\"divID6283\" class=\"leftMenuInActive\"><a id=\"aID6283\" href=\"#\" OnMouseOver=\"link('_dir','curve/curve0',this)\" class=\"leftMenuLinkInActive\">curve</a></div>\n");
document.write("<div id=\"divID6284\" class=\"leftMenuInActive\"><a id=\"aID6284\" href=\"#\" OnMouseOver=\"link('_dir','euler/euler0',this)\" class=\"leftMenuLinkInActive\">euler</a></div>\n");
document.write("<div id=\"divID6285\" class=\"leftMenuInActive\"><a id=\"aID6285\" href=\"#\" OnMouseOver=\"link('_dir','functions/functions0',this)\" class=\"leftMenuLinkInActive\">functions</a></div>\n");
document.write("<div id=\"divID6286\" class=\"leftMenuInActive\"><a id=\"aID6286\" href=\"#\" OnMouseOver=\"link('_dir','matrix/matrix0',this)\" class=\"leftMenuLinkInActive\">matrix</a></div>\n");
document.write("<div id=\"divID6287\" class=\"leftMenuInActive\"><a id=\"aID6287\" href=\"#\" OnMouseOver=\"link('_dir','quaternion/quaternion0',this)\" class=\"leftMenuLinkInActive\">quaternion</a></div>\n");
document.write("<div id=\"divID6288\" class=\"leftMenuInActive\"><a id=\"aID6288\" href=\"#\" OnMouseOver=\"link('_dir','vector/vector0',this)\" class=\"leftMenuLinkInActive\">vector</a></div>\n");
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
